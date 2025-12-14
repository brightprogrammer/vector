#ifndef VECTOR_FUZZER_SETTINGS_HH
#define VECTOR_FUZZER_SETTINGS_HH

#include "types.hh"
#include <string>

///
/// Fuzzer settings retrieved from program
///
struct Settings {
    struct {
        u32 min;
        u32 max;
        u32 step;
    } input_size;
    u32 thread_count;
    u32 max_history_count;
    
    // Target program and tracer paths
    std::string target_program;      // Path to target program to fuzz
    std::string tracer_lib;           // Path to libtracer.so
    std::string drrun_path;           // Path to drrun executable (default: "drrun")
    
    // Output directory for storing checkpoints, crashes, etc.
    std::string work_dir;             // Working directory for fuzzer output (default: "./fuzzer_output")

    // Constructor that parses command line arguments
    Settings(int argc, char* argv[]);
};

#endif // VECTOR_FUZZER_SETTINGS_HH

