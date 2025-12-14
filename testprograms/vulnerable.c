#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    
    // Read input from stdin
    uint8_t buffer[1024];
    ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
    
    if (bytes_read <= 0) {
        return 1;
    }
    
    // Check first character matches 'A'
    if (bytes_read > 0 && buffer[0] == 'A') {
        // Check second character matches 'B'
        if (bytes_read > 1 && buffer[1] == 'B') {
            // Check third character matches 'C'
            if (bytes_read > 2 && buffer[2] == 'C') {
                // Check fourth character matches 'D'
                if (bytes_read > 3 && buffer[3] == 'D') {
                    // Check fifth character matches 'E'
                    if (bytes_read > 4 && buffer[4] == 'E') {
                        // Check sixth character matches 'F'
                        if (bytes_read > 5 && buffer[5] == 'F') {
                            // BUG TRIGGERED: Access invalid memory to cause crash
                            int* ptr = NULL;
                            *ptr = 0xDEADBEEF;  // SIGSEGV
                            return 0;  // Never reached
                        } else {
                            return 1;  // Wrong character at position 5
                        }
                    } else {
                        return 1;  // Wrong character at position 4
                    }
                } else {
                    return 1;  // Wrong character at position 3
                }
            } else {
                return 1;  // Wrong character at position 2
            }
        } else {
            return 1;  // Wrong character at position 1
        }
    } else {
        return 1;  // Wrong character at position 0
    }
}
