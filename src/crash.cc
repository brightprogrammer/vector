#include "crash.hh"
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <sys/wait.h>
#include <cstdint>

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
        throw std::runtime_error("DeserializeCrash: failed to read string length");
    }
    
    std::string str(len, '\0');
    in.read(&str[0], len);
    if (in.fail()) {
        throw std::runtime_error("DeserializeCrash: failed to read string data");
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
        throw std::runtime_error("DeserializeCrash: failed to read u8 vector size");
    }
    
    std::vector<u8> vec(size);
    if (size > 0) {
        in.read(reinterpret_cast<char*>(vec.data()), size * sizeof(u8));
        if (in.fail()) {
            throw std::runtime_error("DeserializeCrash: failed to read u8 vector data");
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
        throw std::runtime_error("DeserializeCrash: failed to read u32 vector size");
    }
    
    std::vector<u32> vec(size);
    if (size > 0) {
        in.read(reinterpret_cast<char*>(vec.data()), size * sizeof(u32));
        if (in.fail()) {
            throw std::runtime_error("DeserializeCrash: failed to read u32 vector data");
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
        throw std::runtime_error("DeserializeCrash: failed to read double");
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
        throw std::runtime_error("DeserializeCrash: failed to read embedding size");
    }
    
    Embedding emb(size);
    if (size > 0) {
        in.read(reinterpret_cast<char*>(emb.data()), size * sizeof(double));
        if (in.fail()) {
            throw std::runtime_error("DeserializeCrash: failed to read embedding data");
        }
    }
    return emb;
}

void SerializeCrash(const CrashInfo& crash_info, const std::string& filepath) {
    std::ofstream out(filepath, std::ios::binary);
    if (!out.is_open()) {
        throw std::runtime_error("SerializeCrash: failed to open file for writing: " + filepath);
    }
    
    // Write endianness
    bool is_little_endian = IsLittleEndian();
    out.write(reinterpret_cast<const char*>(&is_little_endian), sizeof(bool));
    
    // Write signal number
    int signal_number = crash_info.signal_number;
    out.write(reinterpret_cast<const char*>(&signal_number), sizeof(int));
    
    // Write target arguments
    u32 num_args = crash_info.target_args.size();
    out.write(reinterpret_cast<const char*>(&num_args), sizeof(u32));
    for (const auto& arg : crash_info.target_args) {
        WriteString(out, arg);
    }
    
    // Write input
    WriteU8Vector(out, crash_info.input);
    
    // Write trace
    WriteU32Vector(out, crash_info.trace);
    
    // Write graph: embedding_dim
    u32 embedding_dim = crash_info.graph.embedding_dim;
    out.write(reinterpret_cast<const char*>(&embedding_dim), sizeof(u32));
    
    // Write graph: Node2Vec parameters
    WriteDouble(out, crash_info.graph.p);
    WriteDouble(out, crash_info.graph.q);
    u32 walk_length = crash_info.graph.walk_length;
    out.write(reinterpret_cast<const char*>(&walk_length), sizeof(u32));
    u32 num_walks = crash_info.graph.num_walks;
    out.write(reinterpret_cast<const char*>(&num_walks), sizeof(u32));
    u32 window_size = crash_info.graph.window_size;
    out.write(reinterpret_cast<const char*>(&window_size), sizeof(u32));
    WriteDouble(out, crash_info.graph.learning_rate);
    
    // Write graph: graph structure (adjacency list)
    u32 num_nodes = crash_info.graph.graph.size();
    out.write(reinterpret_cast<const char*>(&num_nodes), sizeof(u32));
    for (const auto& graph_entry : crash_info.graph.graph) {
        u32 node = graph_entry.first;
        const std::vector<u32>& neighbors = graph_entry.second;
        out.write(reinterpret_cast<const char*>(&node), sizeof(u32));
        WriteU32Vector(out, neighbors);
    }
    
    // Write graph: embeddings
    u32 num_embeddings = crash_info.graph.embeddings.size();
    out.write(reinterpret_cast<const char*>(&num_embeddings), sizeof(u32));
    for (const auto& emb_entry : crash_info.graph.embeddings) {
        u32 node = emb_entry.first;
        const Embedding& emb = emb_entry.second;
        out.write(reinterpret_cast<const char*>(&node), sizeof(u32));
        WriteEmbedding(out, emb);
    }
    
    // Write ZERO_EMBEDDING
    WriteEmbedding(out, crash_info.graph.ZERO_EMBEDDING);
    
    if (out.fail()) {
        throw std::runtime_error("SerializeCrash: failed to write data to file");
    }
}

void DeserializeCrash(const std::string& filepath, CrashInfo& crash_info) {
    std::ifstream in(filepath, std::ios::binary);
    if (!in.is_open()) {
        throw std::runtime_error("DeserializeCrash: failed to open file for reading: " + filepath);
    }
    
    // Read endianness
    bool is_little_endian;
    in.read(reinterpret_cast<char*>(&is_little_endian), sizeof(bool));
    if (in.fail()) {
        throw std::runtime_error("DeserializeCrash: failed to read endianness");
    }
    crash_info.is_little_endian = is_little_endian;
    
    // Read signal number
    int signal_number;
    in.read(reinterpret_cast<char*>(&signal_number), sizeof(int));
    if (in.fail()) {
        throw std::runtime_error("DeserializeCrash: failed to read signal number");
    }
    crash_info.signal_number = signal_number;
    
    // Check endianness compatibility
    bool current_is_little_endian = IsLittleEndian();
    if (is_little_endian != current_is_little_endian) {
        throw std::runtime_error("DeserializeCrash: endianness mismatch (file is " +
                                (is_little_endian ? std::string("little") : std::string("big")) +
                                "-endian, system is " +
                                (current_is_little_endian ? std::string("little") : std::string("big")) +
                                "-endian)");
    }
    
    // Read target arguments
    u32 num_args;
    in.read(reinterpret_cast<char*>(&num_args), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeCrash: failed to read number of arguments");
    }
    crash_info.target_args.resize(num_args);
    for (u32 i = 0; i < num_args; ++i) {
        crash_info.target_args[i] = ReadString(in);
    }
    
    // Read input
    crash_info.input = ReadU8Vector(in);
    
    // Read trace
    crash_info.trace = ReadU32Vector(in);
    
    // Read graph: embedding_dim
    u32 embedding_dim;
    in.read(reinterpret_cast<char*>(&embedding_dim), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeCrash: failed to read embedding_dim");
    }
    
    // Read graph: Node2Vec parameters
    double p = ReadDouble(in);
    double q = ReadDouble(in);
    u32 walk_length;
    in.read(reinterpret_cast<char*>(&walk_length), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeCrash: failed to read walk_length");
    }
    u32 num_walks;
    in.read(reinterpret_cast<char*>(&num_walks), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeCrash: failed to read num_walks");
    }
    u32 window_size;
    in.read(reinterpret_cast<char*>(&window_size), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeCrash: failed to read window_size");
    }
    double learning_rate = ReadDouble(in);
    
    // Reconstruct graph with parameters (we'll need to manually set members)
    // Note: We can't use the constructor here because we need to set members individually
    // We'll create a temporary and then copy, or use placement new
    crash_info.graph.embedding_dim = embedding_dim;
    crash_info.graph.p = p;
    crash_info.graph.q = q;
    crash_info.graph.walk_length = walk_length;
    crash_info.graph.num_walks = num_walks;
    crash_info.graph.window_size = window_size;
    crash_info.graph.learning_rate = learning_rate;
    
    // Initialize RNG with a default seed (we can't serialize RNG state)
    crash_info.graph.rng = std::mt19937(42);
    
    // Read graph: graph structure (adjacency list)
    u32 num_nodes;
    in.read(reinterpret_cast<char*>(&num_nodes), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeCrash: failed to read number of nodes");
    }
    for (u32 i = 0; i < num_nodes; ++i) {
        u32 node;
        in.read(reinterpret_cast<char*>(&node), sizeof(u32));
        if (in.fail()) {
            throw std::runtime_error("DeserializeCrash: failed to read node ID");
        }
        std::vector<u32> neighbors = ReadU32Vector(in);
        crash_info.graph.graph[node] = neighbors;
    }
    
    // Read graph: embeddings
    u32 num_embeddings;
    in.read(reinterpret_cast<char*>(&num_embeddings), sizeof(u32));
    if (in.fail()) {
        throw std::runtime_error("DeserializeCrash: failed to read number of embeddings");
    }
    for (u32 i = 0; i < num_embeddings; ++i) {
        u32 node;
        in.read(reinterpret_cast<char*>(&node), sizeof(u32));
        if (in.fail()) {
            throw std::runtime_error("DeserializeCrash: failed to read embedding node ID");
        }
        Embedding emb = ReadEmbedding(in);
        crash_info.graph.embeddings[node] = emb;
    }
    
    // Read ZERO_EMBEDDING
    crash_info.graph.ZERO_EMBEDDING = ReadEmbedding(in);
    
    if (in.fail()) {
        throw std::runtime_error("DeserializeCrash: failed to read all data from file");
    }
}

bool IsCrashStatus(int status) {
    return WIFSIGNALED(status);
}

int GetCrashSignal(int status) {
    if (WIFSIGNALED(status)) {
        return WTERMSIG(status);
    }
    return 0;
}

