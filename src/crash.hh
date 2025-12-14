#ifndef VECTOR_FUZZER_CRASH_HH
#define VECTOR_FUZZER_CRASH_HH

#include "types.hh"
#include "graph.hh"
#include <string>
#include <vector>

///
/// Crash information structure
/// Contains all data needed to reproduce a crash
///
struct CrashInfo {
    // Endianness of the system (true = little-endian, false = big-endian)
    bool is_little_endian;
    
    // Signal number that caused the crash (e.g., SIGSEGV, SIGILL)
    // 0 if not a signal termination
    int signal_number;
    
    // Arguments provided to target program
    // This includes the target program path and any command-line arguments
    std::vector<std::string> target_args;
    
    // Input that caused the crash
    FuzzInput input;
    
    // Execution trace captured before crash
    ExecTrace trace;
    
    // Explored graph state at the time of crash
    ExploredGraph graph;
};

///
/// Serialize crash information to a file
/// 
/// @param crash_info The crash information to serialize
/// @param filepath Path to the file where crash data will be written
/// @throws std::runtime_error if file operations fail
///
void SerializeCrash(const CrashInfo& crash_info, const std::string& filepath);

///
/// Deserialize crash information from a file
///
/// @param filepath Path to the file containing serialized crash data
/// @param crash_info Output parameter - will be populated with deserialized data
/// @throws std::runtime_error if file operations fail or data is corrupted
///
void DeserializeCrash(const std::string& filepath, CrashInfo& crash_info);

///
/// Check if a process exit status indicates a crash
/// 
/// @param status The wait status from waitpid()
/// @return true if the process crashed (terminated by signal), false otherwise
///
bool IsCrashStatus(int status);

///
/// Get the signal number that caused the crash
/// 
/// @param status The wait status from waitpid()
/// @return Signal number (e.g., SIGSEGV, SIGILL) or 0 if not a signal termination
///
int GetCrashSignal(int status);

#endif // VECTOR_FUZZER_CRASH_HH

