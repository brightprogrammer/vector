#include "settings.hh"
#include <CLI11.hpp>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdexcept>

// Constructor that parses command line arguments
Settings::Settings(int argc, char* argv[]) {
    // Initialize with default values
    input_size.min = 0;
    input_size.max = 0;
    input_size.step = 0;
    thread_count = 1;
    max_history_count = 100;
    tracer_lib = "./build/libtracer.so";
    drrun_path = "./thirdparty/dynamorio/bin64/drrun";
    work_dir = "./fuzzer_output";
    stdout_redirect = "/dev/null";
    ui_update_freq = 50;  // Default: 50ms update frequency (more responsive)
    seed_path = "";  // Default: no seed directory
  
    // Init command line parser
    CLI::App app{"Vector : An experimental directional fuzzing framework"};
    app.add_option("--max-length", input_size.max, "Maximum input length to write to stdin of target program")->required();
    app.add_option("--min-length", input_size.min, "Minimum input length to write to stdin of target program")->required();
    app.add_option("--step-length", input_size.step, "Step size between maximum and minimum input length")->required();
    app.add_option("--thread-count", thread_count, "Number of fuzzer threads to spawn (default=1)");
    app.add_option("--max-history-count", max_history_count, "Maximum number of interesting historical inputs to store (default=100)");
    
    // Target program and tracer paths
    app.add_option("--target", target_program, "Path to target program to fuzz")->required();
    app.add_option("--tracer", tracer_lib, "Path to libtracer.so (default=./build/libtracer.so)");
    app.add_option("--drrun", drrun_path, "Path to drrun executable (default=drrun)");
    
    // Output directory
    app.add_option("--work-dir", work_dir, "Directory for storing checkpoints, crashes, etc. (default=./fuzzer_output)");
    
    // Target program output redirection
    app.add_option("--stdout-redirect", stdout_redirect, "Redirect target program stdout/stderr to this file (default=/dev/null)");
    
    // UI update frequency
    app.add_option("--ui-update-freq", ui_update_freq, "TUI update frequency in milliseconds (default=100)");
    
    // Seed directory
    app.add_option("--seed-path", seed_path, "Path to directory containing seed inputs to load into history");
       
    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError& e) {
        app.exit(e);
        throw; // Re-throw to let caller handle
    }
    
    // Ensure work directory exists, create if it doesn't
    struct stat st;
    if (stat(work_dir.c_str(), &st) != 0) {
        // Directory doesn't exist, create it
        if (mkdir(work_dir.c_str(), 0755) != 0) {
            throw std::runtime_error("Failed to create work directory: " + work_dir);
        }
    } else {
        // Path exists, check if it's a directory
        if (!S_ISDIR(st.st_mode)) {
            throw std::runtime_error("Work directory path exists but is not a directory: " + work_dir);
        }
    }
}

