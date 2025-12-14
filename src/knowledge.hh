#ifndef VECTOR_FUZZER_KNOWLEDGE_HH
#define VECTOR_FUZZER_KNOWLEDGE_HH

#include "types.hh"
#include "graph.hh"
#include "settings.hh"
#include <vector>

///
/// FuzzerKnowledge holds the accumulated knowledge from fuzzing sessions.
/// It maintains a circular buffer of interesting execution traces and their inputs.
///
struct FuzzerKnowledge {
    std::vector<FuzzExecution> history;  // Circular buffer of executions
    u32 history_index;                   // Current write index in circular buffer
    Settings settings;
    ExploredGraph graph;

    // Constructor
    FuzzerKnowledge(const Settings& s);

    // Add execution to knowledge only if trace is different from existing ones
    // Returns true if execution was added, false if it was a duplicate
    // Automatically serializes knowledge to checkpoint file when execution is added
    bool AddExecutionIfDifferent(const FuzzExecution& execution);
    
    // Set checkpoint filepath for automatic serialization
    void SetCheckpointFilepath(const std::string& filepath);
    
private:
    std::string checkpoint_filepath;  // Filepath for automatic checkpoint serialization
};

///
/// Serialize FuzzerKnowledge to a file
/// 
/// @param knowledge The knowledge to serialize
/// @param filepath Path to the file where knowledge will be written
/// @throws std::runtime_error if file operations fail
///
void SerializeKnowledge(const FuzzerKnowledge& knowledge, const std::string& filepath);

///
/// Deserialize FuzzerKnowledge from a file
///
/// @param filepath Path to the file containing serialized knowledge
/// @return FuzzerKnowledge structure containing the deserialized data
/// @throws std::runtime_error if file operations fail or data is corrupted
///
FuzzerKnowledge DeserializeKnowledge(const std::string& filepath);

#endif // VECTOR_FUZZER_KNOWLEDGE_HH

