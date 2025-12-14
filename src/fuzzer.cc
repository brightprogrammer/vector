#include "fuzzer.hh"
#include "loss.hh"
#include "crash.hh"
#include "shared_trace.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <stdexcept>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <random>
#include <unordered_set>
#include <utility>
#include <ctime>
#include <iomanip>
#include <atomic>
#include <mutex>

// Forward declaration from main.cc
struct ThreadStats {
    std::mutex mutex;
    u32 executions{0};
    u32 crashes{0};
    u32 unique_traces{0};
    std::string status{"Stopped"};
    std::string error_message{""};
    
    void Update(u32 execs, u32 crs, u32 traces, const std::string& st, const std::string& err = "") {
        std::lock_guard<std::mutex> lock(mutex);
        executions = execs;
        crashes = crs;
        unique_traces = traces;
        status = st;
        error_message = err;
    }
    
    void Get(u32& execs, u32& crs, u32& traces, std::string& st, std::string& err) {
        std::lock_guard<std::mutex> lock(mutex);
        execs = executions;
        crs = crashes;
        traces = unique_traces;
        st = status;
        err = error_message;
    }
};

// Internal gradient computation functions (not exposed in header)
namespace {

// Internal function: Compute behavioral gradient (Jacobian matrix) of execution traces with respect to fuzz inputs.
// Uses embeddings to compute distances between nodes in embedding space rather than raw address differences.
// This essentially results in a Jacobian matrix of max dimensions: dy/dx
//
void ComputeBehavioralGradient(BehavioralGradient& grad, ExploredGraph& graph, 
                                const FuzzExecution& fe1, const FuzzExecution& fe2) {
    grad.clear();
  
    const ExecTrace& y1 = fe1.trace;
    const ExecTrace& y2 = fe2.trace;

    const FuzzInput& x1 = fe1.input;
    const FuzzInput& x2 = fe2.input;

    // Ensure graph is updated with both traces
    graph.UpdateGraphFromTrace(y1);
    graph.UpdateGraphFromTrace(y2);
    graph.UpdateEmbeddings();

    u32 dim_y1 = y1.size();
    u32 dim_y2 = y2.size();
    u32 max_dim_y = std::max(dim_y1, dim_y2);

    u32 dim_x1 = x1.size();
    u32 dim_x2 = x2.size();
    u32 max_dim_x = std::max(dim_x1, dim_x2);

    std::vector<double> dy;
    std::vector<double> dx;

    dy.resize(max_dim_y);
    dx.resize(max_dim_x);

    // compute dy using embeddings (distance in embedding space)
    for(u32 i = 0; i < max_dim_y; i++) {
        if (i < y1.size() && i < y2.size()) {
            // Both traces have nodes at position i
            u32 node1 = y1[i];
            u32 node2 = y2[i];
            
            // Compute L2 distance in embedding space
            dy[i] = graph.GetNodeDistance(node1, node2);
        } else if (i < y1.size()) {
            // Only trace1 has a node at position i
            u32 node1 = y1[i];
            // Distance from node1 embedding to zero vector
            dy[i] = graph.GetNodeDistanceWithOrigin(node1);
        } else if (i < y2.size()) {
            // Only trace2 has a node at position i
            u32 node2 = y2[i];
            // Distance from zero vector to node2 embedding
            dy[i] = graph.GetNodeDistanceWithOrigin(node2);
        }
    }

    // compute dx (input differences remain the same)
    for(u32 i = 0; i < max_dim_x; i++) {
        double a = i < x1.size() ? x1[i] : 0;
        double b = i < x2.size() ? x2[i] : 0;
        dx[i] = b - a;
    }

    // compute jacobian matrix
    grad.resize(max_dim_y);
    for(u32 i = 0; i < max_dim_y; i++) {
        grad[i].resize(max_dim_x);
        for(u32 j = 0; j < max_dim_x; j++) {
            if (dx[j] != 0.0) {
                grad[i][j] = dy[i]/dx[j];
            } else {
                grad[i][j] = 0.0;
            }
        }
    }
}

// Internal function: Compute gradient of loss with respect to trace outputs: dL/dy
// 
// Where:
// - L is the embedding loss (higher when walks are similar)
// - y is the ExecTrace (walk)
// - dL/dy is the gradient of loss with respect to trace outputs
//
// forbidden_walk represents the forbidden walk we want to move away from.
// current_walk is the current walk we're optimizing.
//
// Returns dL/dy as a vector where each element dL/dy[i] represents
// how the loss changes with respect to the trace output at position i.
//
void ComputeLossGradientWithTrace(std::vector<double>& dL_dy, ExploredGraph& graph,
                                   const ExecTrace& forbidden_walk,
                                   const ExecTrace& current_walk) {
    dL_dy.clear();
    
    double loss = EmbeddingLoss(graph, forbidden_walk, current_walk);
    
    u32 max_dim_y = std::max(forbidden_walk.size(), current_walk.size());
    dL_dy.resize(max_dim_y, 0.0);
    
    // Compute dy values (embedding distances) for each trace position
    std::vector<double> dy(max_dim_y, 0.0);
    
    for (u32 i = 0; i < max_dim_y; ++i) {
        if (i < forbidden_walk.size() && i < current_walk.size()) {
            u32 node_forbidden = forbidden_walk[i];
            u32 node_current = current_walk[i];
            dy[i] = graph.GetNodeDistance(node_forbidden, node_current);
        } else if (i < forbidden_walk.size()) {
            u32 node_forbidden = forbidden_walk[i];
            dy[i] = graph.GetNodeDistanceWithOrigin(node_forbidden);
        } else if (i < current_walk.size()) {
            u32 node_current = current_walk[i];
            dy[i] = graph.GetNodeDistanceWithOrigin(node_current);
        }
        
        // Compute dL/dy[i] = loss / dy[i] if dy[i] != 0
        // This represents how much the loss changes per unit change in y[i]
        // We want to move away from forbidden walk, so we use the loss value
        if (dy[i] != 0.0) {
            // The gradient should be proportional to loss and inversely proportional to distance
            // Higher loss (more similar) should give stronger gradient to move away
            dL_dy[i] = loss / dy[i];
        } else {
            // If dy[i] is zero, nodes are identical at this position
            // Use loss directly as gradient signal
            dL_dy[i] = loss;
        }
    }
}

} // anonymous namespace

// Forward declaration - function is in anonymous namespace above
FuzzInput GenerateNewInputWithGradientDescent(FuzzerKnowledge& knowledge,
                                               const FuzzExecution& forbidden_execution,
                                               const FuzzExecution& current_execution,
                                               const std::vector<double>& exploration_speed);

///
/// Constructor: creates and attaches to shared memory for this thread
///
FuzzerThread::FuzzerThread(FuzzerKnowledge& k, u32 tid, ThreadStats& s) 
    : knowledge(k), thread_id(tid), shared_trace(nullptr), thread_stats(s) {
    // Construct shared memory name for this thread (generate once)
    // Format: /topfuzz_trace_<thread_id>
    std::ostringstream shm_name_stream;
    shm_name_stream << TOPFUZZ_SHM_NAME_BASE << "_" << thread_id;
    shm_name = shm_name_stream.str();
    
    // Build drrun command arguments (generate once)
    // Format: drrun -c libtracer.so -shm <shm_name> -- <target_program>
    // Store strings to ensure pointers remain valid
    drrun_argv_strings.clear();
    drrun_argv_strings.push_back(knowledge.settings.drrun_path);
    drrun_argv_strings.push_back("-c");
    drrun_argv_strings.push_back(knowledge.settings.tracer_lib);
    drrun_argv_strings.push_back("-shm");
    drrun_argv_strings.push_back(shm_name);
    drrun_argv_strings.push_back("--");
    drrun_argv_strings.push_back(knowledge.settings.target_program);
    
    // Build pointer array for execvp
    drrun_argv.clear();
    for (const auto& str : drrun_argv_strings) {
        drrun_argv.push_back(str.c_str());
    }
    drrun_argv.push_back(nullptr);  // NULL terminator for execvp
    
    // Create shared memory if it doesn't exist
    int fd = shared_trace_create(shm_name.c_str());
    if (fd >= 0) {
        close(fd);  // Close the file descriptor, we'll attach separately
    }
    
    // Attach to shared memory (keep it attached for the lifetime of the thread)
    shared_trace = shared_trace_attach(shm_name.c_str());
    // Note: If attach fails, shared_trace will be nullptr, which ExecOnce will handle
    
    // Calculate thread-specific input size
    // Formula: clamp(min_length + step_size * thread_id, min_length, max_length)
    u32 min_len = knowledge.settings.input_size.min;
    u32 max_len = knowledge.settings.input_size.max;
    u32 step = knowledge.settings.input_size.step;
    u32 calculated_size = min_len + step * thread_id;
    // Clamp to [min_len, max_len]
    thread_input_size = std::max(min_len, std::min(calculated_size, max_len));
}

///
/// Destructor: detaches from shared memory
///
FuzzerThread::~FuzzerThread() {
    if (shared_trace) {
        shared_trace_detach(shared_trace);
        shared_trace = nullptr;
    }
}

///
/// Initialize exploration speed for a given input size
/// All bytes start with positive exploration speed (default_eta)
///
void FuzzerThread::InitializeExplorationSpeed(u32 input_size, double default_eta) {
    exploration_speed.resize(input_size, default_eta);
}

///
/// Update exploration speed: set to -1.0 for bytes that differ between two inputs
/// and resulted in a new trace (not in history)
///
void FuzzerThread::FreezeBytesForNewTrace(const FuzzInput& old_input, const FuzzInput& new_input) {
    u32 max_size = std::max(old_input.size(), new_input.size());
    
    // Ensure exploration_speed is large enough
    if (exploration_speed.size() < max_size) {
        exploration_speed.resize(max_size, 0.01); // Default eta for new bytes
    }
    
    // Find bytes that differ and freeze them (set to -1.0)
    for (u32 i = 0; i < max_size; ++i) {
        u8 old_byte = (i < old_input.size()) ? old_input[i] : 0;
        u8 new_byte = (i < new_input.size()) ? new_input[i] : 0;
        
        if (old_byte != new_byte) {
            // This byte was different and resulted in a new trace
            // Freeze it by setting exploration speed to -1.0
            exploration_speed[i] = -1.0;
        }
    }
}

///
/// Accelerate exploration speed by acceleration amount for all bytes
/// This allows frozen bytes to gradually become mutable again
///
void FuzzerThread::AccelerateExplorationSpeed(double acceleration) {
    for (double& speed : exploration_speed) {
        // Only accelerate if speed is negative (frozen)
        // Clamp to maximum of 1.0
        if (speed < 0.0) {
            speed += acceleration;
            // If speed becomes positive, clamp to reasonable max (e.g., 0.1)
            if (speed > 0.0) {
                speed = std::min(speed, 1.0);
            }
        } else if (speed > 0.0) {
            // For positive speeds, we can also gradually increase them
            // but cap at 1.0
            speed = std::min(speed + acceleration * 0.1, 1.0);
        }
    }
}

///
/// Execute target program once with given input and retrieve execution trace
///
std::pair<FuzzExecution, std::pair<bool, int>> FuzzerThread::ExecOnce(const FuzzInput& input) {
    FuzzExecution execution;
    execution.input = input;
    bool crashed = false;
    int signal_number = 0;
    
    // Enforce invariant: input must be non-empty
    if (input.empty()) {
        throw std::logic_error("ExecOnce: input cannot be empty");
    }
    
    // Use the already-attached shared memory (attached in constructor)
    if (!shared_trace) {
        throw std::logic_error("ExecOnce: shared memory was not attached in constructor");
    }
    
    // Clear shared memory before running target (set trace_count to 0)
    // This signals that no trace is ready yet
    shared_trace->trace_count = 0;
    shared_trace_clear(shared_trace);
    
    // Create pipe to pass input to target program
    int pipe_fds[2];
    if (pipe(pipe_fds) == -1) {
        throw std::runtime_error("ExecOnce: failed to create pipe");
    }
    
    // Fork and execute target program with tracer
    pid_t pid = fork();
    if (pid == 0) {
        // Child process: execute drrun directly
        // Close write end of pipe
        close(pipe_fds[1]);
        
        // Redirect stdin to read from pipe
        if (dup2(pipe_fds[0], STDIN_FILENO) == -1) {
            close(pipe_fds[0]);
            _exit(1);
        }
        close(pipe_fds[0]);
        
        // Execute drrun directly (no shell wrapper)
        execvp(drrun_argv[0], const_cast<char* const*>(drrun_argv.data()));
        _exit(1);  // Should not reach here if execvp succeeds
    } else if (pid > 0) {
        // Parent process: write input to pipe, then wait for child
        close(pipe_fds[0]);  // Close read end
        
        // Write input to pipe
        ssize_t written = write(pipe_fds[1], input.data(), input.size());
        close(pipe_fds[1]);  // Close write end (child will see EOF)
        
        if (written != (ssize_t)input.size()) {
            // Failed to write all input
            waitpid(pid, NULL, 0);  // Clean up child
            throw std::runtime_error("ExecOnce: failed to write all input to pipe");
        }
        
        // Wait for child to complete
        int status;
        waitpid(pid, &status, 0);
        
        // Check if the process crashed (terminated by signal)
        crashed = IsCrashStatus(status);
        if (crashed) {
            signal_number = GetCrashSignal(status);
        }
        
        // Now read the trace from shared memory
        // The tracer writes the trace when the program exits
        // Note: Even if the program crashed, the tracer may have written a partial trace
        uint32_t trace_count = shared_trace->trace_count;
        
        if (trace_count == 0) {
            // If we crashed but have no trace, still create empty trace
            // This is valid for crashes that happen very early
            execution.trace.clear();
        } else {
            // Ensure we don't read more than available
            size_t count_to_read = trace_count;
            if (count_to_read > SHARED_TRACE_MAX_ADDRESSES) {
                count_to_read = SHARED_TRACE_MAX_ADDRESSES;
            }
            
            // Directly copy uint32_t addresses to ExecTrace (which uses u32 = uint32_t)
            execution.trace.resize(count_to_read);
            std::memcpy(execution.trace.data(), shared_trace->addresses, count_to_read * sizeof(uint32_t));
        }
    } else {
        // Fork failed
        throw std::runtime_error("ExecOnce: fork failed");
    }
    
    return std::make_pair(execution, std::make_pair(crashed, signal_number));
}

///
/// Initialization run: generates initial inputs until we have at least 2 executions in knowledge
///
void FuzzerThread::InitializationRun() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<u8> byte_dis(0, 255);
    std::uniform_real_distribution<double> percent_dis(0.10, 0.60);  // 10% to 60%
    
    // Keep running until we have at least 2 executions in knowledge
    while (true) {
        // Count executions in history (runtime invariant: all entries have non-empty traces/inputs)
        // Thread-safe: use snapshot
        std::vector<FuzzExecution> history_snapshot = knowledge.GetHistorySnapshot();
        u32 execution_count = 0;
        for (const auto& exec : history_snapshot) {
            if (!exec.trace.empty()) {
                execution_count++;
            }
        }
        
        // If we have at least 2 executions, we're done
        if (execution_count >= 2) {
            break;
        }
        
        FuzzInput input;
        
        if (execution_count == 0) {
            // Generate first random input with thread-specific size
            input.resize(thread_input_size);
            for (u8& byte : input) {
                byte = byte_dis(gen);
            }
            
            // Initialize exploration speed for initial input size
            InitializeExplorationSpeed(input.size());
        } else {
            // We have 1 execution, generate second input by mutating the first
            // Find the first execution in history (runtime invariant: it has non-empty trace/input)
            // Thread-safe: use snapshot
            FuzzInput first_input;
            u32 original_first_input_size = 0;
            for (const auto& exec : history_snapshot) {
                if (!exec.trace.empty()) {
                    first_input = exec.input;
                    original_first_input_size = exec.input.size();
                    break;
                }
            }
            
            // Resize to thread-specific size if needed
            if (first_input.size() != thread_input_size) {
                first_input.resize(thread_input_size);
                // Fill with random bytes if we're expanding
                if (first_input.size() > original_first_input_size) {
                    for (u32 i = original_first_input_size; i < first_input.size(); ++i) {
                        first_input[i] = byte_dis(gen);
                    }
                }
            }
            
            // Generate second input by mutating the first input
            // Mutate 10% to 60% of bytes randomly
            input = first_input;
            double mutation_percent = percent_dis(gen);
            u32 num_bytes_to_mutate = static_cast<u32>(input.size() * mutation_percent);
            if (num_bytes_to_mutate == 0 && input.size() > 0) {
                num_bytes_to_mutate = 1;  // Mutate at least one byte
            }
            
            // Randomly select bytes to mutate
            std::uniform_int_distribution<u32> index_dis(0, input.size() - 1);
            std::unordered_set<u32> mutated_indices;
            for (u32 i = 0; i < num_bytes_to_mutate; ++i) {
                u32 idx;
                do {
                    idx = index_dis(gen);
                } while (mutated_indices.count(idx) > 0);
                mutated_indices.insert(idx);
                
                // Mutate this byte to a random value
                input[idx] = byte_dis(gen);
            }
            
            // Update exploration speed if input size changed
            if (input.size() != exploration_speed.size()) {
                InitializeExplorationSpeed(input.size());
            }
        }
        
        // Execute input
        auto exec_result = ExecOnce(input);
        FuzzExecution execution = exec_result.first;
        bool crashed = exec_result.second.first;
        int signal_number = exec_result.second.second;
        
        // If crashed, serialize crash information
        if (crashed) {
            CrashInfo crash_info;
            crash_info.is_little_endian = true; // Will be detected in serialization
            crash_info.signal_number = signal_number;
            // Extract target program arguments from drrun_argv_strings
            // Format: drrun -c libtracer.so -shm <shm_name> -- <target_program> [args...]
            // We want everything after "--"
            bool found_separator = false;
            for (const auto& arg : drrun_argv_strings) {
                if (found_separator) {
                    crash_info.target_args.push_back(arg);
                } else if (arg == "--") {
                    found_separator = true;
                }
            }
            crash_info.input = execution.input;
            crash_info.trace = execution.trace;
            // Thread-safe: copy graph data (without mutex)
            {
                std::lock_guard<std::mutex> lock(knowledge.knowledge_mutex);
                crash_info.graph.CopyGraphData(knowledge.graph);
            }
            
            // Generate crash filename with thread ID, signal, and timestamp
            std::ostringstream crash_filename;
            crash_filename << knowledge.settings.work_dir << "/crash_thread" << thread_id << "_sig" << signal_number << "_";
            auto now = std::time(nullptr);
            auto tm = *std::localtime(&now);
            crash_filename << std::put_time(&tm, "%Y%m%d_%H%M%S") << ".crash";
            
            try {
                SerializeCrash(crash_info, crash_filename.str());
                // Update global crash stats
                extern std::atomic<u32> g_crash_count;
                g_crash_count++;
            } catch (const std::exception& e) {
                // Log error but don't stop fuzzing
                // In a real implementation, you'd want proper logging
            }
        }
        
        // Add execution to knowledge only if trace is non-empty
        // (AddExecutionIfDifferent enforces non-empty trace/input invariant)
        // Skip empty traces (e.g., from very early crashes before any basic blocks executed)
        if (!execution.trace.empty()) {
            knowledge.AddExecutionIfDifferent(execution);
        }
        // Update global execution counter even if we skip empty traces
        extern std::atomic<u32> g_total_executions;
        g_total_executions++;
    }
}

///
/// Run the fuzzing loop: generate inputs, execute them, and add unique executions to knowledge
///
void FuzzerThread::Run() {
    // First, ensure we have at least 2 executions in history
    // Count executions (runtime invariant: all stored entries have non-empty traces/inputs)
    // Thread-safe: use snapshot
    std::vector<FuzzExecution> history_snapshot = knowledge.GetHistorySnapshot();
    u32 valid_executions = 0;
    for (const auto& exec : history_snapshot) {
        if (!exec.trace.empty()) {
            valid_executions++;
        }
    }
    
    // If we don't have at least 2 executions, run initialization
    if (valid_executions < 2) {
        InitializationRun();
    }
    
    // Initialize exploration speed for thread-specific input size first
    // This ensures exploration_speed always matches thread_input_size
    if (exploration_speed.size() != thread_input_size) {
        InitializeExplorationSpeed(thread_input_size);
    }
    
    // Get current execution from history (use the most recent one)
    // Runtime invariant: history always has non-empty traces and inputs
    // Thread-safe: use snapshot and index
    history_snapshot = knowledge.GetHistorySnapshot();
    u32 history_idx = knowledge.GetHistoryIndex();
    u32 latest_idx = (history_idx + knowledge.settings.max_history_count - 1) % knowledge.settings.max_history_count;
    const FuzzExecution& latest_exec = history_snapshot[latest_idx];
    FuzzExecution current_execution = latest_exec;
    FuzzInput current_input = latest_exec.input;
    
    // Resize input to thread-specific size if needed
    // Each thread uses a different input size based on its thread_id
    if (current_input.size() != thread_input_size) {
        current_input.resize(thread_input_size);
        // Fill with random bytes if we're expanding
        if (current_input.size() > latest_exec.input.size()) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<u8> byte_dis(0, 255);
            for (u32 i = latest_exec.input.size(); i < current_input.size(); ++i) {
                current_input[i] = byte_dis(gen);
            }
        }
        // Update current_execution to reflect the resized input
        current_execution.input = current_input;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<u8> byte_dis(0, 255);
    
    // Main fuzzing loop
    // Runtime invariant: we always have at least 2 executions in history (guaranteed by InitializationRun)
    // Check external stop flag (declared in main.cc)
    extern std::atomic<bool> g_should_stop_fuzzing;
    while (true) {
        // Check stop flag at start of each iteration
        if (g_should_stop_fuzzing.load()) {
            break;
        }
        // Pick a forbidden execution from history (randomly)
        // Thread-safe: use snapshot
        history_snapshot = knowledge.GetHistorySnapshot();
        std::uniform_int_distribution<u32> history_dis(0, knowledge.settings.max_history_count - 1);
        u32 forbidden_idx = history_dis(gen);
        const FuzzExecution* forbidden_execution = nullptr;
        
        // Find a valid execution in history (runtime invariant: all entries have non-empty traces/inputs)
        for (u32 i = 0; i < knowledge.settings.max_history_count; ++i) {
            u32 idx = (forbidden_idx + i) % knowledge.settings.max_history_count;
            const auto& exec = history_snapshot[idx];
            if (!exec.trace.empty()) {
                forbidden_execution = &exec;
                break;
            }
        }
        
        // Generate new input using gradient descent
        // Runtime invariant: forbidden_execution should always be found (we have at least 2 executions)
        if (!forbidden_execution) {
            throw std::logic_error("Run: no forbidden execution found in history (invariant violation)");
        }
        
        // Create copies of executions with thread-specific input sizes
        // This ensures all inputs match thread_input_size for gradient computation
        FuzzExecution forbidden_exec_resized = *forbidden_execution;
        if (forbidden_exec_resized.input.size() != thread_input_size) {
            forbidden_exec_resized.input.resize(thread_input_size);
            // Fill with random bytes if expanding
            if (forbidden_exec_resized.input.size() > forbidden_execution->input.size()) {
                for (u32 i = forbidden_execution->input.size(); i < forbidden_exec_resized.input.size(); ++i) {
                    forbidden_exec_resized.input[i] = byte_dis(gen);
                }
            }
        }
        
        // Ensure current_execution.input matches thread_input_size
        if (current_execution.input.size() != thread_input_size) {
            current_execution.input.resize(thread_input_size);
            // Fill with random bytes if expanding
            if (current_execution.input.size() > current_input.size()) {
                for (u32 i = current_input.size(); i < current_execution.input.size(); ++i) {
                    current_execution.input[i] = byte_dis(gen);
                }
            }
            current_input = current_execution.input;
        }
        
        FuzzInput old_input = current_input;
        current_input = GenerateNewInputWithGradientDescent(
            knowledge,
            forbidden_exec_resized,
            current_execution,
            exploration_speed
        );
        
        // Ensure input size matches thread-specific size
        if (current_input.size() != thread_input_size) {
            current_input.resize(thread_input_size);
            // Fill with random bytes if we're expanding
            if (current_input.size() > old_input.size()) {
                for (u32 i = old_input.size(); i < current_input.size(); ++i) {
                    current_input[i] = byte_dis(gen);
                }
            }
        }
        
        // Ensure exploration speed matches thread-specific size
        if (exploration_speed.size() != thread_input_size) {
            InitializeExplorationSpeed(thread_input_size);
        }
        
        // Execute the new input
        auto exec_result = ExecOnce(current_input);
        FuzzExecution new_execution = exec_result.first;
        bool crashed = exec_result.second.first;
        int signal_number = exec_result.second.second;
        
        // If crashed, serialize crash information
        if (crashed) {
            CrashInfo crash_info;
            crash_info.is_little_endian = true; // Will be detected in serialization
            crash_info.signal_number = signal_number;
            // Extract target program arguments from drrun_argv_strings
            // Format: drrun -c libtracer.so -shm <shm_name> -- <target_program> [args...]
            // We want everything after "--"
            bool found_separator = false;
            for (const auto& arg : drrun_argv_strings) {
                if (found_separator) {
                    crash_info.target_args.push_back(arg);
                } else if (arg == "--") {
                    found_separator = true;
                }
            }
            crash_info.input = new_execution.input;
            crash_info.trace = new_execution.trace;
            // Thread-safe: copy graph data (without mutex)
            {
                std::lock_guard<std::mutex> lock(knowledge.knowledge_mutex);
                crash_info.graph.CopyGraphData(knowledge.graph);
            }
            
            // Generate crash filename with thread ID, signal, and timestamp
            std::ostringstream crash_filename;
            crash_filename << knowledge.settings.work_dir << "/crash_thread" << thread_id << "_sig" << signal_number << "_";
            auto now = std::time(nullptr);
            auto tm = *std::localtime(&now);
            crash_filename << std::put_time(&tm, "%Y%m%d_%H%M%S") << ".crash";
            
            try {
                SerializeCrash(crash_info, crash_filename.str());
                // Update global crash stats
                extern std::atomic<u32> g_crash_count;
                g_crash_count++;
            } catch (const std::exception& e) {
                // Log error but don't stop fuzzing
                // In a real implementation, you'd want proper logging
            }
        }
        
        // Check stop flag before continuing
        if (g_should_stop_fuzzing.load()) {
            break;
        }
        
        // Check if this execution is unique and add to knowledge
        // AddExecutionIfDifferent enforces non-empty trace/input invariant
        // Skip empty traces (e.g., from very early crashes before any basic blocks executed)
        bool was_added = false;
        if (!new_execution.trace.empty()) {
            was_added = knowledge.AddExecutionIfDifferent(new_execution);
        }
        // Update global execution counter even if we skip empty traces
        extern std::atomic<u32> g_total_executions;
        g_total_executions++;
        
        // If execution was added (new trace), freeze bytes that changed
        if (was_added) {
            FreezeBytesForNewTrace(current_execution.input, new_execution.input);
        }
        
        // Accelerate exploration speed (gradually unfreeze bytes)
        AccelerateExplorationSpeed();
        
        // Update current execution for next iteration
        current_execution = new_execution;
    }
}

// Internal function: Generate new input using gradient descent with per-byte exploration speed
// 
// Uses chain rule: dL/dx = (dy/dx)^T * dL/dy
// Then updates input: x_new = x_current - exploration_speed * dL/dx
//
// forbidden_execution: Execution from history that we want to move away from
// current_execution: Current execution to optimize
// exploration_speed: Per-byte exploration speed vector (values from -1.0 to 1.0)
//                    If <= 0: byte won't be changed
//                    If > 0: value is used as eta for that byte
//
// Returns new input generated using gradient descent
//
FuzzInput GenerateNewInputWithGradientDescent(FuzzerKnowledge& knowledge,
                                               const FuzzExecution& forbidden_execution,
                                               const FuzzExecution& current_execution,
                                               const std::vector<double>& exploration_speed) {
    ExploredGraph& graph = knowledge.graph;
    
    // Step 1: Compute dL/dy (gradient of loss with respect to trace outputs)
    std::vector<double> dL_dy;
    ComputeLossGradientWithTrace(dL_dy, graph, forbidden_execution.trace, current_execution.trace);
    
    // Step 2: Compute Jacobian matrix dy/dx
    BehavioralGradient jacobian;
    ComputeBehavioralGradient(jacobian, graph, forbidden_execution, current_execution);
    
    if (jacobian.empty() || jacobian[0].empty() || dL_dy.empty()) {
        throw std::logic_error("Cannot compute gradient: jacobian or dL/dy is empty");
    }
    
    u32 max_dim_y = jacobian.size();
    if (max_dim_y == 0) {
        throw std::logic_error("Cannot compute gradient: jacobian has zero rows");
    }
    
    u32 max_dim_x = jacobian[0].size();
    
    // Verify all jacobian rows have the same size
    for (u32 i = 0; i < max_dim_y; ++i) {
        if (jacobian[i].size() != max_dim_x) {
            throw std::logic_error("Cannot compute gradient: jacobian rows have inconsistent sizes");
        }
    }
    
    // Check compatibility for matrix multiplication: (dy/dx)^T * dL/dy
    // jacobian is [max_dim_y][max_dim_x], so (dy/dx)^T is [max_dim_x][max_dim_y]
    // dL/dy is [max_dim_y]
    // For multiplication to work: number of columns of (dy/dx)^T (which is max_dim_y) 
    // must equal size of dL/dy (which is also max_dim_y)
    if (max_dim_y != dL_dy.size()) {
        throw std::logic_error("Cannot compute gradient: jacobian and dL/dy are not compatible for matrix multiplication (jacobian rows != dL/dy size)");
    }
    
    // Step 3: Compute dL/dx using chain rule: dL/dx = (dy/dx)^T * dL/dy
    // Matrix multiplication: jacobian^T * dL_dy
    // jacobian is [max_dim_y][max_dim_x], so jacobian^T is [max_dim_x][max_dim_y]
    // dL_dy is [max_dim_y]
    // Result dL_dx is [max_dim_x]
    std::vector<double> dL_dx(max_dim_x, 0.0);
    
    // Matrix multiplication: dL_dx = jacobian^T * dL_dy
    // For each output dimension j in dL_dx:
    for (u32 j = 0; j < max_dim_x; ++j) {
        double sum = 0.0;
        // Sum over all input dimensions i:
        for (u32 i = 0; i < max_dim_y; ++i) {
            // jacobian^T[j][i] = jacobian[i][j]
            // So: dL_dx[j] = sum_i (jacobian[i][j] * dL_dy[i])
            sum += jacobian[i][j] * dL_dy[i];
        }
        dL_dx[j] = sum;
    }
    
    // Step 4: Gradient descent update with per-byte exploration speed
    // x_new = x_current - exploration_speed * dL/dx
    const FuzzInput& x_current = current_execution.input;
    FuzzInput x_new;
    x_new.resize(max_dim_x);
    
    // Enforce invariant: exploration_speed size must match input size
    if (exploration_speed.size() != max_dim_x) {
        throw std::logic_error("GenerateNewInputWithGradientDescent: exploration_speed size does not match input size");
    }
    
    for (u32 j = 0; j < max_dim_x; ++j) {
        double x_j = (j < x_current.size()) ? (double)x_current[j] : 0.0;
        
        // Get exploration speed for this byte
        double eta = exploration_speed[j];
        
        // If exploration speed <= 0, don't change this byte
        if (eta <= 0.0) {
            x_new[j] = (j < x_current.size()) ? x_current[j] : 0;
            continue;
        }
        
        // Apply gradient update: x_new = x_current - eta * dL/dx
        double update = x_j - eta * dL_dx[j];
        
        // Wrap around to 0 when crossing 255, clamp negative values to 0
        if (update < 0.0) {
            update = 0.0;
        } else if (update > 255.0) {
            // Round back to 0 when crossing 255 mark
            update = std::fmod(update, 256.0);
        }
        
        x_new[j] = (u8)std::round(update);
    }
    
    return x_new;
}

