#ifndef VECTOR_FUZZER_TYPES_HH
#define VECTOR_FUZZER_TYPES_HH

#include <vector>
#include <cstdint>

typedef uint32_t u32;
typedef uint64_t u64;
typedef uint8_t u8;

///
/// Represents an execution trace of program
/// Addresses are virtual addresses in program based off of 0
///
typedef std::vector<u32> ExecTrace;

///
/// Represents a generated fuzz input provided to target program
///
typedef std::vector<u8> FuzzInput;

///
/// Mapping of a fuzzer generated input with it's corresponding trace.
/// This is used to handle current generated traces and store the interesting ones as well.
/// This is also in a sense a representation of a behavior of the target program.
/// 
struct FuzzExecution {
    ExecTrace trace;
    FuzzInput input;    
};

#endif // VECTOR_FUZZER_TYPES_HH
