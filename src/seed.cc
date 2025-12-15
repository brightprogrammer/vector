#include "seed.hh"
#include "shared_trace.h"
#include "crash.hh"
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <cstring>
#include <stdexcept>
#include <iostream>

// Helper function to execute target program with given input and get trace
// Similar to FuzzerThread::ExecOnce but standalone for seed loading
static std::pair<FuzzExecution, std::pair<bool, int>> ExecuteWithInput(
    const FuzzInput& input,
    const Settings& settings,
    const std::string& shm_name) {
    
    FuzzExecution execution;
    execution.input = input;
    bool crashed = false;
    int signal_number = 0;
    
    // Enforce invariant: input must be non-empty
    if (input.empty()) {
        throw std::logic_error("ExecuteWithInput: input cannot be empty");
    }
    
    // Attach to shared memory
    SharedTrace* shared_trace = shared_trace_attach(shm_name.c_str());
    if (!shared_trace) {
        throw std::runtime_error("ExecuteWithInput: failed to attach to shared memory");
    }
    
    // Clear shared memory before running target
    shared_trace->trace_count = 0;
    shared_trace_clear(shared_trace);
    
    // Build drrun command arguments
    std::vector<std::string> drrun_argv_strings;
    drrun_argv_strings.push_back(settings.drrun_path);
    drrun_argv_strings.push_back("-c");
    drrun_argv_strings.push_back(settings.tracer_lib);
    drrun_argv_strings.push_back("-shm");
    drrun_argv_strings.push_back(shm_name);
    drrun_argv_strings.push_back("--");
    drrun_argv_strings.push_back(settings.target_program);
    
    std::vector<const char*> drrun_argv;
    for (const auto& str : drrun_argv_strings) {
        drrun_argv.push_back(str.c_str());
    }
    drrun_argv.push_back(nullptr);
    
    // Create pipe to pass input to target program
    int pipe_fds[2];
    if (pipe(pipe_fds) == -1) {
        shared_trace_detach(shared_trace);
        throw std::runtime_error("ExecuteWithInput: failed to create pipe");
    }
    
    // Fork and execute target program with tracer
    pid_t pid = fork();
    if (pid == 0) {
        // Child process: execute drrun
        close(pipe_fds[1]);
        
        // Redirect stdin to read from pipe
        if (dup2(pipe_fds[0], STDIN_FILENO) == -1) {
            close(pipe_fds[0]);
            _exit(1);
        }
        close(pipe_fds[0]);
        
        // Redirect stdout and stderr
        int redirect_fd;
        if (settings.stdout_redirect == "/dev/null") {
            redirect_fd = open("/dev/null", O_WRONLY);
        } else {
            redirect_fd = open(settings.stdout_redirect.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
        }
        
        if (redirect_fd == -1) {
            redirect_fd = open("/dev/null", O_WRONLY);
            if (redirect_fd == -1) {
                _exit(1);
            }
        }
        
        if (dup2(redirect_fd, STDOUT_FILENO) == -1) {
            close(redirect_fd);
            _exit(1);
        }
        if (dup2(redirect_fd, STDERR_FILENO) == -1) {
            close(redirect_fd);
            _exit(1);
        }
        close(redirect_fd);
        
        // Execute drrun
        execvp(drrun_argv[0], const_cast<char* const*>(drrun_argv.data()));
        _exit(1);
    } else if (pid > 0) {
        // Parent process: write input to pipe, then wait for child
        close(pipe_fds[0]);
        
        // Write input to pipe
        ssize_t written = write(pipe_fds[1], input.data(), input.size());
        close(pipe_fds[1]);
        
        if (written != (ssize_t)input.size()) {
            waitpid(pid, NULL, 0);
            shared_trace_detach(shared_trace);
            throw std::runtime_error("ExecuteWithInput: failed to write all input to pipe");
        }
        
        // Wait for child to complete
        int status;
        waitpid(pid, &status, 0);
        
        // Check if the process crashed
        crashed = IsCrashStatus(status);
        if (crashed) {
            signal_number = GetCrashSignal(status);
        }
        
        // Read the trace from shared memory
        uint32_t trace_count = shared_trace->trace_count;
        
        if (trace_count == 0) {
            execution.trace.clear();
        } else {
            size_t count_to_read = trace_count;
            if (count_to_read > SHARED_TRACE_MAX_ADDRESSES) {
                count_to_read = SHARED_TRACE_MAX_ADDRESSES;
            }
            
            execution.trace.resize(count_to_read);
            std::memcpy(execution.trace.data(), shared_trace->addresses, count_to_read * sizeof(uint32_t));
        }
        
        // Detach from shared memory
        shared_trace_detach(shared_trace);
    } else {
        // Fork failed
        shared_trace_detach(shared_trace);
        throw std::runtime_error("ExecuteWithInput: fork failed");
    }
    
    return std::make_pair(execution, std::make_pair(crashed, signal_number));
}

u32 LoadSeedsFromDirectory(const std::string& seed_dir, FuzzerKnowledge& knowledge, const Settings& settings) {
    // Check if directory exists
    struct stat st;
    if (stat(seed_dir.c_str(), &st) != 0) {
        throw std::runtime_error("LoadSeedsFromDirectory: seed directory does not exist: " + seed_dir);
    }
    if (!S_ISDIR(st.st_mode)) {
        throw std::runtime_error("LoadSeedsFromDirectory: seed path is not a directory: " + seed_dir);
    }
    
    // Create shared memory for seed loading (use a unique name)
    std::string shm_name = "/topfuzz_trace_seed_loader";
    int fd = shared_trace_create(shm_name.c_str());
    if (fd >= 0) {
        close(fd);
    }
    
    u32 loaded_count = 0;
    u32 skipped_count = 0;
    
    // Open directory
    DIR* dir = opendir(seed_dir.c_str());
    if (!dir) {
        throw std::runtime_error("LoadSeedsFromDirectory: failed to open directory: " + seed_dir);
    }
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        // Skip . and ..
        if (entry->d_name[0] == '.' && (entry->d_name[1] == '\0' || 
            (entry->d_name[1] == '.' && entry->d_name[2] == '\0'))) {
            continue;
        }
        
        // Build full path
        std::string filepath = seed_dir + "/" + entry->d_name;
        
        // Check if it's a regular file
        struct stat file_st;
        if (stat(filepath.c_str(), &file_st) != 0) {
            continue;  // Skip if stat fails
        }
        if (!S_ISREG(file_st.st_mode)) {
            continue;  // Skip if not a regular file
        }
        
        // Read file contents
        std::ifstream file(filepath, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "[!] Failed to open seed file: " << filepath << std::endl;
            skipped_count++;
            continue;
        }
        
        // Read entire file into input vector
        FuzzInput input;
        file.seekg(0, std::ios::end);
        std::streamsize file_size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        if (file_size > 0) {
            input.resize(file_size);
            file.read(reinterpret_cast<char*>(input.data()), file_size);
        }
        file.close();
        
        // Skip empty files
        if (input.empty()) {
            skipped_count++;
            continue;
        }
        
        try {
            // Execute program with seed input
            auto exec_result = ExecuteWithInput(input, settings, shm_name);
            FuzzExecution execution = exec_result.first;
            bool crashed = exec_result.second.first;
            int signal_number = exec_result.second.second;
            
            // Handle crashes (log but continue)
            if (crashed) {
                std::cerr << "[!] Seed file caused crash (signal " << signal_number 
                          << "): " << filepath << std::endl;
            }
            
            // Add to knowledge only if trace is non-empty
            if (!execution.trace.empty()) {
                bool was_added = knowledge.AddExecutionIfDifferent(execution);
                if (was_added) {
                    loaded_count++;
                    std::cout << "[+] Loaded seed: " << filepath 
                              << " (trace length: " << execution.trace.size() << ")" << std::endl;
                } else {
                    skipped_count++;
                    std::cout << "[-] Skipped duplicate seed: " << filepath << std::endl;
                }
            } else {
                skipped_count++;
                std::cout << "[-] Skipped seed with empty trace: " << filepath << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "[!] Error processing seed file " << filepath << ": " << e.what() << std::endl;
            skipped_count++;
        }
    }
    
    closedir(dir);
    
    // Clean up shared memory (try to detach if still attached)
    SharedTrace* cleanup_trace = shared_trace_attach(shm_name.c_str());
    if (cleanup_trace) {
        shared_trace_detach(cleanup_trace);
    }
    
    std::cout << "[*] Seed loading complete: " << loaded_count << " loaded, " 
              << skipped_count << " skipped" << std::endl;
    
    return loaded_count;
}
