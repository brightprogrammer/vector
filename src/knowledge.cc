#include "knowledge.hh"
#include <cstring>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <cstdint>

FuzzerKnowledge::FuzzerKnowledge(const Settings& s)
    : history_index(0), settings(s), graph(4, 42, 1.0, 1.0, 10, 5, 3, 0.025), checkpoint_filepath() {
    // Initialize circular buffer with max_history_count capacity
    // Graph uses default Node2Vec parameters (can be made configurable later)
    history.resize(settings.max_history_count);
    
    // Set default checkpoint filepath in work directory
    checkpoint_filepath = settings.work_dir + "/knowledge_checkpoint.knowledge";
}

bool FuzzerKnowledge::AddExecutionIfDifferent(const FuzzExecution& execution) {
    // Enforce invariant: only non-empty traces and inputs can be stored
    if (execution.trace.empty()) {
        throw std::logic_error("Cannot add execution with empty trace to knowledge");
    }
    if (execution.input.empty()) {
        throw std::logic_error("Cannot add execution with empty input to knowledge");
    }

    // Thread-safe: lock mutex for entire operation
    std::lock_guard<std::mutex> lock(knowledge_mutex);

    // Check if trace is different from all existing traces in history
    // Runtime invariant: all entries in history have non-empty traces and inputs
    for (u32 i = 0; i < history.size(); ++i) {
        const ExecTrace& existing_trace = history[i].trace;
        const ExecTrace& new_trace = execution.trace;

        // If sizes are different, traces are different
        if (existing_trace.size() != new_trace.size()) {
            continue;  // Different size, check next
        }

        // If sizes are same, compare data (both are non-empty by invariant)
        if (std::memcmp(existing_trace.data(), new_trace.data(),
                       existing_trace.size() * sizeof(u32)) == 0) {
            // Traces are identical, don't add
            return false;
        }
    }

    // Trace is different, add to circular buffer
    history[history_index] = execution;
    history_index = (history_index + 1) % settings.max_history_count;
    
    // Update graph with the new trace (adds nodes and edges)
    graph.UpdateGraphFromTrace(execution.trace);
    // Update embeddings after adding new nodes/edges
    graph.UpdateEmbeddings();

    // Automatically serialize knowledge to checkpoint file if filepath is set
    if (!checkpoint_filepath.empty()) {
        try {
            SerializeKnowledge(*this, checkpoint_filepath);
        } catch (...) {
            // If serialization fails, don't fail the add operation
            // Just continue - checkpoint is best-effort
        }
    }
    
    // Notify that a new execution was added (for main.cc to print summary)
    // This is done by returning true, and main.cc will detect the change

    return true;
}

std::vector<FuzzExecution> FuzzerKnowledge::GetHistorySnapshot() const {
    std::lock_guard<std::mutex> lock(knowledge_mutex);
    return history;
}

u32 FuzzerKnowledge::GetHistoryIndex() const {
    std::lock_guard<std::mutex> lock(knowledge_mutex);
    return history_index;
}

void FuzzerKnowledge::SetCheckpointFilepath(const std::string& filepath) {
    checkpoint_filepath = filepath;
}

// Helper function to check endianness
static bool IsLittleEndian() {
    uint32_t test = 0x01020304;
    uint8_t* bytes = reinterpret_cast<uint8_t*>(&test);
    return bytes[0] == 0x04;
}

// Helper function to write a string to file
static void WriteString(std::ofstream& out, const std::string& str) {
    u32 len = str.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(u32));
    out.write(str.data(), len);
}

// Helper function to read a string from file
static std::string ReadString(std::ifstream& in) {
    u32 len;
    in.read(reinterpret_cast<char*>(&len), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read string length");
    }
    
    std::string str(len, '\0');
    in.read(&str[0], len);
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read string data");
    }
    return str;
}

// Helper function to write a vector of u8
static void WriteU8Vector(std::ofstream& out, const std::vector<u8>& vec) {
    u32 size = vec.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(u32));
    if (size > 0) {
        out.write(reinterpret_cast<const char*>(vec.data()), size * sizeof(u8));
    }
}

// Helper function to read a vector of u8
static std::vector<u8> ReadU8Vector(std::ifstream& in) {
    u32 size;
    in.read(reinterpret_cast<char*>(&size), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read u8 vector size");
    }
    
    std::vector<u8> vec(size);
    if (size > 0) {
        in.read(reinterpret_cast<char*>(vec.data()), size * sizeof(u8));
        if (in.fail()) {
            throw std::runtime_error("DeserializeKnowledge: failed to read u8 vector data");
        }
    }
    return vec;
}

// Helper function to write a vector of u32
static void WriteU32Vector(std::ofstream& out, const std::vector<u32>& vec) {
    u32 size = vec.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(u32));
    if (size > 0) {
        out.write(reinterpret_cast<const char*>(vec.data()), size * sizeof(u32));
    }
}

// Helper function to read a vector of u32
static std::vector<u32> ReadU32Vector(std::ifstream& in) {
    u32 size;
    in.read(reinterpret_cast<char*>(&size), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read u32 vector size");
    }
    
    std::vector<u32> vec(size);
    if (size > 0) {
        in.read(reinterpret_cast<char*>(vec.data()), size * sizeof(u32));
        if (in.fail()) {
            throw std::runtime_error("DeserializeKnowledge: failed to read u32 vector data");
        }
    }
    return vec;
}

// Helper function to write a double
static void WriteDouble(std::ofstream& out, double value) {
    out.write(reinterpret_cast<const char*>(&value), sizeof(double));
}

// Helper function to read a double
static double ReadDouble(std::ifstream& in) {
    double value;
    in.read(reinterpret_cast<char*>(&value), sizeof(double));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read double");
    }
    return value;
}

// Helper function to write an Embedding
static void WriteEmbedding(std::ofstream& out, const Embedding& emb) {
    u32 size = emb.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(u32));
    if (size > 0) {
        out.write(reinterpret_cast<const char*>(emb.data()), size * sizeof(double));
    }
}

// Helper function to read an Embedding
static Embedding ReadEmbedding(std::ifstream& in) {
    u32 size;
    in.read(reinterpret_cast<char*>(&size), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read embedding size");
    }
    
    Embedding emb(size);
    if (size > 0) {
        in.read(reinterpret_cast<char*>(emb.data()), size * sizeof(double));
        if (in.fail()) {
            throw std::runtime_error("DeserializeKnowledge: failed to read embedding data");
        }
    }
    return emb;
}

// Helper function to write FuzzExecution
static void WriteFuzzExecution(std::ofstream& out, const FuzzExecution& exec) {
    WriteU32Vector(out, exec.trace);
    WriteU8Vector(out, exec.input);
}

// Helper function to read FuzzExecution
static FuzzExecution ReadFuzzExecution(std::ifstream& in) {
    FuzzExecution exec;
    exec.trace = ReadU32Vector(in);
    exec.input = ReadU8Vector(in);
    return exec;
}

void SerializeKnowledge(const FuzzerKnowledge& knowledge, const std::string& filepath) {
    std::ofstream out(filepath, std::ios::binary);
    if (!out.is_open()) {
        throw std::runtime_error("SerializeKnowledge: failed to open file for writing: " + filepath);
    }
    
    // Write endianness
    bool is_little_endian = IsLittleEndian();
    out.write(reinterpret_cast<const char*>(&is_little_endian), sizeof(bool));
    
    // Write Settings
    out.write(reinterpret_cast<const char*>(&knowledge.settings.input_size.min), sizeof(u32));
    out.write(reinterpret_cast<const char*>(&knowledge.settings.input_size.max), sizeof(u32));
    out.write(reinterpret_cast<const char*>(&knowledge.settings.input_size.step), sizeof(u32));
    out.write(reinterpret_cast<const char*>(&knowledge.settings.thread_count), sizeof(u32));
    out.write(reinterpret_cast<const char*>(&knowledge.settings.max_history_count), sizeof(u32));
    WriteString(out, knowledge.settings.target_program);
    WriteString(out, knowledge.settings.tracer_lib);
    WriteString(out, knowledge.settings.drrun_path);
    WriteString(out, knowledge.settings.work_dir);
    
    // Write history_index
    out.write(reinterpret_cast<const char*>(&knowledge.history_index), sizeof(u32));
    
    // Write history (circular buffer)
    u32 history_size = knowledge.history.size();
    out.write(reinterpret_cast<const char*>(&history_size), sizeof(u32));
    for (const auto& exec : knowledge.history) {
        WriteFuzzExecution(out, exec);
    }
    
    // Write graph: embedding_dim
    u32 embedding_dim = knowledge.graph.embedding_dim;
    out.write(reinterpret_cast<const char*>(&embedding_dim), sizeof(u32));
    
    // Write graph: Node2Vec parameters
    WriteDouble(out, knowledge.graph.p);
    WriteDouble(out, knowledge.graph.q);
    u32 walk_length = knowledge.graph.walk_length;
    out.write(reinterpret_cast<const char*>(&walk_length), sizeof(u32));
    u32 num_walks = knowledge.graph.num_walks;
    out.write(reinterpret_cast<const char*>(&num_walks), sizeof(u32));
    u32 window_size = knowledge.graph.window_size;
    out.write(reinterpret_cast<const char*>(&window_size), sizeof(u32));
    WriteDouble(out, knowledge.graph.learning_rate);
    
    // Write graph: graph structure (adjacency list)
    u32 num_nodes = knowledge.graph.graph.size();
    out.write(reinterpret_cast<const char*>(&num_nodes), sizeof(u32));
    for (const auto& graph_entry : knowledge.graph.graph) {
        u32 node = graph_entry.first;
        const std::vector<u32>& neighbors = graph_entry.second;
        out.write(reinterpret_cast<const char*>(&node), sizeof(u32));
        WriteU32Vector(out, neighbors);
    }
    
    // Write graph: embeddings
    u32 num_embeddings = knowledge.graph.embeddings.size();
    out.write(reinterpret_cast<const char*>(&num_embeddings), sizeof(u32));
    for (const auto& emb_entry : knowledge.graph.embeddings) {
        u32 node = emb_entry.first;
        const Embedding& emb = emb_entry.second;
        out.write(reinterpret_cast<const char*>(&node), sizeof(u32));
        WriteEmbedding(out, emb);
    }
    
    // Write ZERO_EMBEDDING
    WriteEmbedding(out, knowledge.graph.ZERO_EMBEDDING);
    
    if (out.fail()) {
        throw std::runtime_error("SerializeKnowledge: failed to write data to file");
    }
}

void DeserializeKnowledge(const std::string& filepath, FuzzerKnowledge& knowledge) {
    std::ifstream in(filepath, std::ios::binary);
    if (!in.is_open()) {
        throw std::runtime_error("DeserializeKnowledge: failed to open file for reading: " + filepath);
    }
    
    // Read endianness
    bool is_little_endian;
    in.read(reinterpret_cast<char*>(&is_little_endian), sizeof(bool));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read endianness");
    }
    
    // Check endianness compatibility
    bool current_is_little_endian = IsLittleEndian();
    if (is_little_endian != current_is_little_endian) {
        throw std::runtime_error("DeserializeKnowledge: endianness mismatch (file is " +
                                (is_little_endian ? std::string("little") : std::string("big")) +
                                "-endian, system is " +
                                (current_is_little_endian ? std::string("little") : std::string("big")) +
                                "-endian)");
    }
    
    // Read Settings
    Settings settings(0, nullptr); // We'll reconstruct it
    in.read(reinterpret_cast<char*>(&settings.input_size.min), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read input_size.min");
    }
    in.read(reinterpret_cast<char*>(&settings.input_size.max), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read input_size.max");
    }
    in.read(reinterpret_cast<char*>(&settings.input_size.step), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read input_size.step");
    }
    in.read(reinterpret_cast<char*>(&settings.thread_count), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read thread_count");
    }
    in.read(reinterpret_cast<char*>(&settings.max_history_count), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read max_history_count");
    }
    settings.target_program = ReadString(in);
    settings.tracer_lib = ReadString(in);
    settings.drrun_path = ReadString(in);
    settings.work_dir = ReadString(in);
    
    // Reconstruct knowledge with deserialized settings
    // We can't assign because of mutex, so we need to manually set members
    // First, create a new knowledge object and copy data
    FuzzerKnowledge temp_knowledge(settings);
    knowledge.history = temp_knowledge.history;
    knowledge.history_index = temp_knowledge.history_index;
    knowledge.settings = settings;
    knowledge.graph.CopyGraphData(temp_knowledge.graph);
    
    // Read history_index
    in.read(reinterpret_cast<char*>(&knowledge.history_index), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read history_index");
    }
    
    // Read history (circular buffer)
    u32 history_size;
    in.read(reinterpret_cast<char*>(&history_size), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read history size");
    }
    knowledge.history.resize(history_size);
    for (u32 i = 0; i < history_size; ++i) {
        knowledge.history[i] = ReadFuzzExecution(in);
    }
    
    // Read graph: embedding_dim
    u32 embedding_dim;
    in.read(reinterpret_cast<char*>(&embedding_dim), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read embedding_dim");
    }
    
    // Read graph: Node2Vec parameters
    double p = ReadDouble(in);
    double q = ReadDouble(in);
    u32 walk_length;
    in.read(reinterpret_cast<char*>(&walk_length), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read walk_length");
    }
    u32 num_walks;
    in.read(reinterpret_cast<char*>(&num_walks), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read num_walks");
    }
    u32 window_size;
    in.read(reinterpret_cast<char*>(&window_size), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read window_size");
    }
    double learning_rate = ReadDouble(in);
    
    // Reconstruct graph with parameters
    knowledge.graph.embedding_dim = embedding_dim;
    knowledge.graph.p = p;
    knowledge.graph.q = q;
    knowledge.graph.walk_length = walk_length;
    knowledge.graph.num_walks = num_walks;
    knowledge.graph.window_size = window_size;
    knowledge.graph.learning_rate = learning_rate;
    
    // Initialize RNG with a default seed (we can't serialize RNG state)
    knowledge.graph.rng = std::mt19937(42);
    
    // Read graph: graph structure (adjacency list)
    u32 num_nodes;
    in.read(reinterpret_cast<char*>(&num_nodes), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read number of nodes");
    }
    for (u32 i = 0; i < num_nodes; ++i) {
        u32 node;
        in.read(reinterpret_cast<char*>(&node), sizeof(u32));
        if (in.fail()) {
            throw std::runtime_error("DeserializeKnowledge: failed to read node ID");
        }
        std::vector<u32> neighbors = ReadU32Vector(in);
        knowledge.graph.graph[node] = neighbors;
    }
    
    // Read graph: embeddings
    u32 num_embeddings;
    in.read(reinterpret_cast<char*>(&num_embeddings), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read number of embeddings");
    }
    for (u32 i = 0; i < num_embeddings; ++i) {
        u32 node;
        in.read(reinterpret_cast<char*>(&node), sizeof(u32));
        if (in.fail()) {
            throw std::runtime_error("DeserializeKnowledge: failed to read embedding node ID");
        }
        Embedding emb = ReadEmbedding(in);
        knowledge.graph.embeddings[node] = emb;
    }
    
    // Read ZERO_EMBEDDING
    knowledge.graph.ZERO_EMBEDDING = ReadEmbedding(in);
    
    if (in.fail()) {
        throw std::runtime_error("DeserializeKnowledge: failed to read all data from file");
    }
}
