// dynamorio
#include <dr_api.h>
#include <drvector.h>
#include <dr_os_utils.h>

// libc
#include <stdint.h>
#include <string.h>
#include <stdio.h>

// unix includes
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <errno.h>

// shared memory for trace communication
#include "shared_trace.h"

// Stores basic context for this client
typedef struct TopFuzzTracer {
    // stores addresses of basic blocks that are executed
    drvector_t exec_trace;
    
    // stores all input data read by the program
    drvector_t input_chunks;      // stores pointers to input data chunks
    drvector_t input_chunk_sizes; // stores sizes of each chunk
    uint64_t total_input_size;
    
    app_pc app_start;
    app_pc app_end;

    // Target app's command line (read from /proc/self/cmdline)
    int app_argc;
    char** app_argv;
    
    // Set to 1 when app_pc first enters program range
    // Any read after this is a direct/indirect decision of the app
    int app_code_executing;
    
    // temporary storage for read syscall interception
    void* pending_read_buf;
    size_t pending_read_size;
} TopFuzzTracer;

TopFuzzTracer tf = {0};

// Shared memory name passed from fuzzer via command-line arguments
static const char* g_shm_name = NULL;

// No trace file writing - only shared memory communication

static void bb_exec_trace(app_pc start_pc);

// Read target app's command line from /proc/self/cmdline
static void read_app_cmdline(void) {
    file_t f = dr_open_file("/proc/self/cmdline", DR_FILE_READ);
    if (f == INVALID_FILE) {
        dr_printf("[topfuzz] Warning: could not read /proc/self/cmdline\n");
        return;
    }
    
    // Read the cmdline (null-separated arguments)
    char buf[4096] = {0};
    ssize_t len = dr_read_file(f, buf, sizeof(buf) - 1);
    dr_close_file(f);
    
    if (len <= 0) {
        return;
    }
    
    // Count arguments (number of null terminators before end)
    int argc = 0;
    for (ssize_t i = 0; i < len; i++) {
        if (buf[i] == '\0') {
            argc++;
        }
    }
    
    if (argc == 0) {
        return;
    }
    
    // Allocate argv array
    tf.app_argv = (char**)dr_global_alloc(argc * sizeof(char*));
    if (!tf.app_argv) {
        return;
    }
    
    // Parse arguments
    tf.app_argc = 0;
    char* ptr = buf;
    while (ptr < buf + len && tf.app_argc < argc) {
        size_t arg_len = strlen(ptr);
        if (arg_len > 0) {
            tf.app_argv[tf.app_argc] = (char*)dr_global_alloc(arg_len + 1);
            if (tf.app_argv[tf.app_argc]) {
                memcpy(tf.app_argv[tf.app_argc], ptr, arg_len + 1);
                tf.app_argc++;
            }
        }
        ptr += arg_len + 1;
    }
    
    // Don't print - fuzzer will show stats
}

// Free app command line
static void free_app_cmdline(void) {
    if (tf.app_argv) {
        for (int i = 0; i < tf.app_argc; i++) {
            if (tf.app_argv[i]) {
                dr_global_free(tf.app_argv[i], strlen(tf.app_argv[i]) + 1);
            }
        }
        dr_global_free(tf.app_argv, tf.app_argc * sizeof(char*));
        tf.app_argv = NULL;
        tf.app_argc = 0;
    }
}

// Collect all input data into a single buffer
static uint8_t* collect_input_data(uint64_t* out_size) {
    *out_size = tf.total_input_size;
    if (tf.total_input_size == 0) {
        return NULL;
    }
    
    uint8_t* buffer = (uint8_t*)dr_global_alloc(tf.total_input_size);
    if (!buffer) {
        return NULL;
    }
    
    uint64_t offset = 0;
    uint num_chunks = tf.input_chunks.entries;
    for (uint i = 0; i < num_chunks; i++) {
        void* chunk = drvector_get_entry(&tf.input_chunks, i);
        size_t chunk_size = (size_t)(uintptr_t)drvector_get_entry(&tf.input_chunk_sizes, i);
        memcpy(buffer + offset, chunk, chunk_size);
        offset += chunk_size;
        
    }
    
    return buffer;
}

// Free all input chunks
static void free_input_chunks(void) {
    uint num_chunks = tf.input_chunks.entries;
    for (uint i = 0; i < num_chunks; i++) {
        void* chunk = drvector_get_entry(&tf.input_chunks, i);
        size_t chunk_size = (size_t)(uintptr_t)drvector_get_entry(&tf.input_chunk_sizes, i);
        dr_global_free(chunk, chunk_size);
    }
}

// Compute hash of captured input (djb2 algorithm)
static uint32_t compute_input_hash(void) {
    if (tf.total_input_size == 0) {
        return 0;
    }
    
    uint32_t hash = 5381;  // djb2 initial value
    uint num_chunks = tf.input_chunks.entries;
    
    for (uint i = 0; i < num_chunks; i++) {
        const uint8_t* chunk = (const uint8_t*)drvector_get_entry(&tf.input_chunks, i);
        size_t chunk_size = (size_t)(uintptr_t)drvector_get_entry(&tf.input_chunk_sizes, i);
        
        for (size_t j = 0; j < chunk_size; j++) {
            hash = ((hash << 5) + hash) + chunk[j];  // hash * 33 + chunk[j]
        }
    }
    
    return hash;
}

static void event_exit(void) {
    // Use shared memory name parsed in dr_client_main
    if (!g_shm_name) {
        dr_printf("[topfuzz] ERROR: Shared memory name not set! This should not happen.\n");
        dr_exit_process(1);
        return;  // Never reached
    }
    
    SharedTrace* shm = shared_trace_attach(g_shm_name);
    if (!shm) {
        // Failed to attach to shared memory - exit with special code
        dr_printf("[topfuzz] FATAL: Failed to attach to shared memory: %s\n", g_shm_name);
        dr_exit_process(0xcafebabe);
        return;  // Never reached
    }
    
    // Write trace in binary format: first uint64_t is count, then addresses
    uint num_addrs = tf.exec_trace.entries;
    
    // Write addresses as uint32_t values (offsets from app_start)
    // Make sure we don't overflow the shared memory buffer
    uint max_write = (num_addrs < SHARED_TRACE_MAX_ADDRESSES) ? num_addrs : SHARED_TRACE_MAX_ADDRESSES;
    
    // Write addresses using simple writes
    for (uint i = 0; i < max_write; i++) {
        uint64_t offset = (uint64_t)drvector_get_entry(&tf.exec_trace, i);
        // Cast to uint32_t (offsets should fit in 32 bits)
        shm->addresses[i] = (uint32_t)offset;
    }
    
    // Compute hash of the input that was read
    uint32_t input_hash = compute_input_hash();
    
    // Write input hash
    shm->input_hash = input_hash;
    
    // Write trace count LAST (after writing addresses and input hash)
    shm->trace_count = (uint32_t)max_write;
    
    shared_trace_detach(shm);
    
    // Note: We're not cleaning up vectors/chunks here to avoid potential crashes
    // DynamoRIO will clean up on process exit anyway
}

static dr_emit_flags_t event_bb(void *drcontext, void* tag, instrlist_t *bb, bool for_trace, bool translating) {
    // get basic block start address
    app_pc start_pc = (app_pc)tag;
  
    // if basic block is outside program range then return
    // we don't wanna count functions inside libraries like libc, like when __libc_start_main is called
    if(start_pc < tf.app_start || start_pc >= tf.app_end) {
        return DR_EMIT_DEFAULT;
    }

    // instrument by installing a function call with both start and end addresses
    dr_insert_clean_call(
        drcontext,
        bb, /* list of instructions in this basic block */
        instrlist_first_app(bb), /* instrument first instruction */
        (void*)bb_exec_trace, /* call to insert in instrumentation */
        false /* dont save fpstate*/,
        1 /* only one argument: start_pc */,
        OPND_CREATE_INTPTR((intptr_t)start_pc) /* start address */
    );
    
    return DR_EMIT_DEFAULT;
}

// Filter which syscalls we want to intercept
static char event_filter_syscall(void *drcontext, int sysnum) {
    // We only care about read syscall (SYS_read = 0 on x86_64 Linux)
    return (sysnum == SYS_read);
}

// Called before syscall execution
// Note: DynamoRIO expects 'bool' (char), not '_Bool'
static char event_pre_syscall(void *drcontext, int sysnum) {
    if (sysnum == SYS_read && tf.app_code_executing) {
        // Only capture after app code has started executing
        // read(int fd, void *buf, size_t count)
        // Save buffer pointer and size for post-syscall capture
        tf.pending_read_buf = (void*)dr_syscall_get_param(drcontext, 1);
        tf.pending_read_size = (size_t)dr_syscall_get_param(drcontext, 2);
    }
    return 1; // execute the syscall (return 1 for true, 0 for false)
}

// Called after syscall execution
static void event_post_syscall(void *drcontext, int sysnum) {
    if (sysnum == SYS_read && tf.app_code_executing) {
        // Only capture after app code has started executing
        // Get the return value (number of bytes actually read)
        ssize_t bytes_read = (ssize_t)dr_syscall_get_result(drcontext);
        
        if (bytes_read > 0 && tf.pending_read_buf != NULL) {
            // Allocate a copy of the data that was read
            void* data_copy = dr_global_alloc(bytes_read);
            if (data_copy) {
                memcpy(data_copy, tf.pending_read_buf, bytes_read);
                
                // Store the chunk and its size
                drvector_append(&tf.input_chunks, data_copy);
                drvector_append(&tf.input_chunk_sizes, (void*)(uintptr_t)bytes_read);
                tf.total_input_size += bytes_read;
                
                // Don't print - fuzzer will show stats
            }
        }
        
        // Clear pending state
        tf.pending_read_buf = NULL;
        tf.pending_read_size = 0;
    }
}

DR_EXPORT void dr_client_main(client_id_t tid, int argc, const char* argv[]) {
    (void)tid;  // unused

    // Parse shared memory name from command-line arguments
    // Expected format: drrun -c libclient.so -shm <shm_name> -- <target>
    for (int i = 0; i < argc - 1; i++) {
        if (strcmp(argv[i], "-shm") == 0) {
            g_shm_name = argv[i + 1];
            break;
        }
    }
    
    if (!g_shm_name) {
        dr_printf("[topfuzz] ERROR: Shared memory name not provided via -shm argument!\n");
        dr_printf("[topfuzz] Usage: drrun -c libtracer.so -shm <shm_name> -- <target>\n");
        dr_exit_process(1);
        return;  // Never reached
    }
    
    // get app base and end to avoid code executions inside library
    module_data_t* mod = dr_get_main_module();
    tf.app_start = mod->start;
    tf.app_end = mod->end;
    dr_free_module_data(mod);

    // Read target app's command line from /proc/self/cmdline
    read_app_cmdline();

    // initialize trace storage
    drvector_init(&tf.exec_trace, 32, false, NULL);
    
    // initialize input capture storage
    drvector_init(&tf.input_chunks, 16, false, NULL);
    drvector_init(&tf.input_chunk_sizes, 16, false, NULL);
    tf.total_input_size = 0;

    // register basic block instrumentation
    // Cast to match DynamoRIO's expected signature (bool is char in C++ context)
    dr_register_bb_event((dr_emit_flags_t (*)(void *, void *, instrlist_t *, char, char))event_bb);
    
    // register syscall interception for input capture
    // Cast to match DynamoRIO's expected signature (bool is char in C++ context)
    dr_register_filter_syscall_event((char (*)(void *, int))event_filter_syscall);
    dr_register_pre_syscall_event(event_pre_syscall);
    dr_register_post_syscall_event(event_post_syscall);
    
    // register exit handler
    dr_register_exit_event(event_exit);
}

static void bb_exec_trace(app_pc start_pc) {
    // First time entering app code - mark that app is now executing
    if (!tf.app_code_executing) {
        tf.app_code_executing = 1;
    }

    uint64_t start_offset = (uint64_t)(start_pc - tf.app_start);
    drvector_append(&tf.exec_trace, (void*)start_offset);
}
