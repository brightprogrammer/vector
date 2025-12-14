#ifndef VECTOR_FUZZER_GRAPH_HH
#define VECTOR_FUZZER_GRAPH_HH

#include "types.hh"
#include <vector>
#include <unordered_map>
#include <random>
#include <mutex>

///
/// Graph module maintains a graph structure from execution traces.
/// Execution traces represent walks in the graph (nodes are basic block addresses,
/// edges represent transitions between basic blocks).
/// The module continuously maintains graph embeddings for computing distances
/// between walks in the embedding space.
///

///
/// Embedding represents a vector of floating-point values that encode
/// the learned representation of a node in the graph.
///
typedef std::vector<double> Embedding;

///
/// ExploredGraph holds all data for a graph structure and its embeddings.
/// Execution traces are added to the graph, which updates nodes and edges.
/// The graph continuously maintains embeddings for all nodes using Node2Vec algorithm.
///
struct ExploredGraph {
    std::unordered_map<u32, std::vector<u32>> graph;       // adjacency list
    std::unordered_map<u32, Embedding> embeddings;          // node embeddings
    u32 embedding_dim;                                      // embedding dimension
    std::mt19937 rng;                                       // random generator
    mutable std::mutex graph_mutex;                          // Protects graph and embeddings access

    // Node2Vec parameters
    double p;                                               // return parameter (BFS bias)
    double q;                                               // in-out parameter (DFS bias)
    u32 walk_length;                                        // length of random walks
    u32 num_walks;                                          // number of walks per node
    u32 window_size;                                        // Skip-gram window size
    double learning_rate;                                   // learning rate for SGD

    // Constructor with Node2Vec parameters
    ExploredGraph(u32 dim = 4, u32 seed = 42,
                  double p_param = 1.0, double q_param = 1.0,
                  u32 walk_len = 10, u32 walks = 5,
                  u32 window = 3, double lr = 0.025)
        : embedding_dim(dim), rng(seed),
          p(p_param), q(q_param), walk_length(walk_len),
          num_walks(walks), window_size(window), learning_rate(lr),
          ZERO_EMBEDDING(dim, 0.0) {}

    // Update graph with a new trace (walk)
    // Adds new nodes and edges as encountered in the trace
    // Automatically initializes embeddings for new nodes
    void UpdateGraphFromTrace(const ExecTrace& trace);

    // Update embeddings for all nodes in the graph using Node2Vec algorithm
    // Generates biased random walks and trains embeddings using Skip-gram
    void UpdateEmbeddings();

    // Compute mean embedding of a trace (walk)
    // Returns the average embedding vector of all nodes in the trace
    Embedding MeanEmbedding(const ExecTrace& trace) const;

    // Get embedding for a specific node (returns empty embedding if node doesn't exist)
    // Thread-safe: uses internal mutex
    Embedding GetNodeEmbedding(u32 node) const {
        std::lock_guard<std::mutex> lock(graph_mutex);
        if (embeddings.count(node)) {
            return embeddings.at(node);
        }
        return Embedding(embedding_dim, 0.0);
    }

    // Compute L2 distance between two embeddings
    // Returns the Euclidean distance in embedding space
    double EmbeddingDistance(const Embedding& emb1, const Embedding& emb2) const;

    // Get distance between two nodes in embedding space
    // Returns the Euclidean distance between the embeddings of the two nodes
    double GetNodeDistance(u32 node1, u32 node2) const;

    // Get distance between a node and the origin (zero embedding)
    // Returns the Euclidean distance from the node's embedding to zero
    double GetNodeDistanceWithOrigin(u32 node) const;

    // Zero embedding (origin in embedding space)
    // Initialized in constructor with instance's embedding_dim
    Embedding ZERO_EMBEDDING;
    
    // Copy graph data (without mutex) - for serialization/crash info
    // Thread-safe: locks both this and other's mutexes
    void CopyGraphData(const ExploredGraph& other);

private:
    // Generate a biased random walk starting from a node
    std::vector<u32> GenerateBiasedRandomWalk(u32 start_node);

    // Get transition probability for Node2Vec biased random walk
    double GetTransitionProbability(u32 prev_node, u32 curr_node, u32 next_node);

    // Train embeddings using Skip-gram on a walk
    void TrainSkipGram(const std::vector<u32>& walk);
};

#endif // VECTOR_FUZZER_GRAPH_HH

