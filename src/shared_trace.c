#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#include "shared_trace.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int shared_trace_create(const char* name) {
    // First, try to unlink any existing shared memory with this name
    // This ensures we start with a clean slate and prevents conflicts
    shm_unlink(name);
    
    // Create shared memory object (should succeed now that we unlinked)
    int fd = shm_open(name, O_CREAT | O_RDWR | O_EXCL, 0666);
    if (fd < 0) {
        // If creation still fails, something is wrong
        return -1;
    }
    
    // Set size
    if (ftruncate(fd, SHARED_TRACE_SIZE) < 0) {
        close(fd);
        shm_unlink(name);
        return -1;
    }
    
    return fd;
}

SharedTrace* shared_trace_attach(const char* name) {
    int fd = shm_open(name, O_RDWR, 0666);
    if (fd < 0) {
        return NULL;
    }
    
    // Map shared memory
    SharedTrace* shm = (SharedTrace*)mmap(NULL, SHARED_TRACE_SIZE,
                                          PROT_READ | PROT_WRITE,
                                          MAP_SHARED, fd, 0);
    close(fd);
    
    if (shm == MAP_FAILED) {
        return NULL;
    }
    
    return shm;
}

void shared_trace_detach(SharedTrace* shm) {
    if (shm) {
        munmap(shm, SHARED_TRACE_SIZE);
    }
}

int shared_trace_unlink(const char* name) {
    return shm_unlink(name);
}

void shared_trace_clear(SharedTrace* shm) {
    if (shm) {
        shm->trace_count = 0;
    }
}

int shared_trace_parse_addresses(SharedTrace* shm, uint64_t* addresses, size_t max_count) {
    if (!shm || !addresses || max_count == 0) {
        return -1;
    }
    
    // Read trace count
    uint32_t trace_length = shm->trace_count;
    
    if (trace_length == 0) {
        return 0;  // Empty trace
    }
    
    // Ensure we don't read more than available or requested
    size_t count_to_read = trace_length;
    if (count_to_read > max_count) {
        count_to_read = max_count;
    }
    if (count_to_read > SHARED_TRACE_MAX_ADDRESSES) {
        count_to_read = SHARED_TRACE_MAX_ADDRESSES;
    }
    
    // Convert uint32_t addresses to uint64_t (zero-extend)
    // Simple reads - parent waits for child, so no race condition
    for (size_t i = 0; i < count_to_read; i++) {
        addresses[i] = (uint64_t)shm->addresses[i];
    }
    
    return (int)count_to_read;
}
