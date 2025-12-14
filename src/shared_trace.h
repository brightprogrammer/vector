#ifndef SHARED_TRACE_H
#define SHARED_TRACE_H

#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>

// Base shared memory name for trace communication
// Each thread will use: /topfuzz_trace_<thread_id>
#define TOPFUZZ_SHM_NAME_BASE "/topfuzz_trace"

// Simple shared memory structure for trace communication
// Layout:
//   trace_count: uint32_t - number of addresses in the trace (max ~4 billion)
//   addresses: uint32_t[] - the actual trace addresses (offsets from app_start)
//   input_hash: uint32_t - hash of the input that produced this trace (for verification)
#define SHARED_TRACE_MAX_ADDRESSES ((16 * 1024 * 1024) / sizeof(uint32_t))  // ~4M addresses max (16MB / 4 bytes)

typedef struct {
    uint32_t trace_count;  // Number of addresses in the trace
    uint32_t addresses[SHARED_TRACE_MAX_ADDRESSES];  // The actual trace addresses (offsets as uint32_t)
    uint32_t input_hash;  // Hash of the input that produced this trace (stored at the end)
} SharedTrace;

// Size of shared memory segment
#define SHARED_TRACE_SIZE (sizeof(SharedTrace))

// Create or open shared memory segment
// Returns file descriptor on success, -1 on error
int shared_trace_create(const char* name);

// Attach to existing shared memory segment
// Returns pointer to SharedTrace on success, NULL on error
SharedTrace* shared_trace_attach(const char* name);

// Detach from shared memory
void shared_trace_detach(SharedTrace* shm);

// Unlink shared memory segment
int shared_trace_unlink(const char* name);

// Clear trace data (set length=0)
void shared_trace_clear(SharedTrace* shm);

// Read addresses from shared trace (binary format)
// Reads trace_count, then copies that many uint32_t values and converts to uint64_t
// Returns number of addresses read, or -1 on error
int shared_trace_parse_addresses(SharedTrace* shm, uint64_t* addresses, size_t max_count);

#endif // SHARED_TRACE_H
