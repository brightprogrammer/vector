#ifndef VECTOR_FUZZER_SEED_HH
#define VECTOR_FUZZER_SEED_HH

#include "knowledge.hh"
#include "types.hh"
#include "settings.hh"
#include <string>
#include <vector>

///
/// Load seed inputs from a directory and add them to knowledge
/// 
/// Reads all files from the seed directory, executes the target program
/// with each file's contents as input, captures execution traces, and
/// adds them to the knowledge history.
///
/// @param seed_dir Path to directory containing seed input files
/// @param knowledge FuzzerKnowledge to add executions to
/// @param settings Settings containing target program and tracer paths
/// @return Number of seed inputs successfully loaded
///
u32 LoadSeedsFromDirectory(const std::string& seed_dir, FuzzerKnowledge& knowledge, const Settings& settings);

#endif // VECTOR_FUZZER_SEED_HH
