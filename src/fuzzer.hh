#ifndef VECTOR_FUZZER_FUZZER_HH
#define VECTOR_FUZZER_FUZZER_HH

#include "knowledge.hh"
#include "types.hh"
#include "graph.hh"
#include "shared_trace.h"
#include <vector>
#include <string>

///
/// Represents the Jacobian matrix retrieved after computation of gradient
/// of execution traces (outputs) with respect to inputs
///
typedef std::vector<std::vector<double>> BehavioralGradient;

///
/// FuzzerThread represents a single fuzzing thread.
/// Each thread has access to shared knowledge for coordination.
///
struct FuzzerThread {
    FuzzerKnowledge& knowledge;
    u32 thread_id;  // Thread identifier for shared memory name
    SharedTrace* shared_trace;  // Shared memory for trace communication (attached in constructor)
    std::string shm_name;  // Shared memory name (generated once in constructor)
    std::vector<std::string> drrun_argv_strings;  // Store strings for drrun arguments
    std::vector<const char*> drrun_argv;  // Command arguments for drrun (pointers to drrun_argv_strings)
    
    // Exploration speed for each input byte position
    // Values range from -1.0 to 1.0
    // - If <= 0: byte won't be changed (frozen)
    // - If > 0: value is used as eta (learning rate) for that byte
    // - Set to -1.0 for bytes that were different and resulted in new trace
    // - Gradually increases with acceleration 0.001 to allow mutation again
    std::vector<double> exploration_speed;
    
    // Constructor: attaches to shared memory for this thread
    FuzzerThread(FuzzerKnowledge& k, u32 tid);
    
    // Destructor: detaches from shared memory
    ~FuzzerThread();
    
    // Initialize exploration speed for a given input size
    // All bytes start with positive exploration speed (default_eta)
    void InitializeExplorationSpeed(u32 input_size, double default_eta = 0.01);
    
    // Update exploration speed: set to -1.0 for bytes that differ between two inputs
    // and resulted in a new trace (not in history)
    void FreezeBytesForNewTrace(const FuzzInput& old_input, const FuzzInput& new_input);
    
    // Accelerate exploration speed by 0.001 for all bytes
    // This allows frozen bytes to gradually become mutable again
    void AccelerateExplorationSpeed(double acceleration = 0.001);
    
    // Execute target program once with given input and retrieve execution trace
    // Uses shared memory to get trace from the tracer
    // Returns FuzzExecution containing the input and its execution trace
    // Also returns crash status: (crashed: bool, signal_number: int)
    // If crashed is true, signal_number contains the signal that terminated the process
    std::pair<FuzzExecution, std::pair<bool, int>> ExecOnce(const FuzzInput& input);
    
    // Initialization run: generates two initial inputs to bootstrap the fuzzing process
    // First input is random, second input is a mutation of the first (10-60% bytes changed)
    // Returns when we have at least 2 executions in history
    void InitializationRun();
    
    // Run the fuzzing loop: generate inputs, execute them, and add unique executions to knowledge
    // This is the main fuzzing loop that runs continuously
    // Requires at least 2 executions in history (call InitializationRun first if needed)
    void Run();
};

#endif // VECTOR_FUZZER_FUZZER_HH

