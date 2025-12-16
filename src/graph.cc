#include "graph.hh"
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <stdexcept>
#include <mutex>

// Update graph with a new trace (walk)
// Adds new nodes and edges as encountered in the trace
// Automatically initializes embeddings for new nodes
// Thread-safe: uses internal mutex
void ExploredGraph::UpdateGraphFromTrace(const ExecTrace& trace) {
    std::lock_guard<std::mutex> lock(graph_mutex);
    
    for (u32 i = 0; i < trace.size(); ++i) {
        u32 node = trace[i];
        
        // Initialize node if it doesn't exist
        if (!graph.count(node)) {
            graph[node] = {};
        }
        
        // Initialize embedding for new nodes
        if (!embeddings.count(node)) {
            // Initialize embedding with small random values (Xavier/Glorot-like initialization)
            // Small random values help with gradient stability and convergence
            Embedding emb(embedding_dim);
            std::uniform_real_distribution<double> dist(-0.1, 0.1);
            for (u32 j = 0; j < embedding_dim; ++j) {
                emb[j] = dist(rng);
            }
            embeddings[node] = emb;
        }

        // Add edge from current node to next node (if exists)
        if (i + 1 < trace.size()) {
            u32 next_node = trace[i+1];
            // Check if edge already exists to avoid duplicates
            auto& neighbors = graph[node];
            if (std::find(neighbors.begin(), neighbors.end(), next_node) == neighbors.end()) {
                neighbors.push_back(next_node);
            }
        }
    }
}

// Update embeddings for all nodes in the graph using Node2Vec algorithm
// Generates biased random walks and trains embeddings using Skip-gram
void ExploredGraph::UpdateEmbeddings() {
    if (graph.empty() || embeddings.empty()) {
        return;
    }

    // Generate random walks and train embeddings
    for (u32 walk_iter = 0; walk_iter < num_walks; ++walk_iter) {
        // Generate a walk from each node
        for (const auto& graph_entry : graph) {
            u32 node = graph_entry.first;
            if (graph[node].empty()) continue; // Skip isolated nodes
            
            std::vector<u32> walk = GenerateBiasedRandomWalk(node);
            if (walk.size() >= 2) {
                TrainSkipGram(walk);
            }
        }
    }
}

// Generate a biased random walk starting from a node
std::vector<u32> ExploredGraph::GenerateBiasedRandomWalk(u32 start_node) {
    std::vector<u32> walk;
    walk.reserve(walk_length);
    
    if (!graph.count(start_node) || graph[start_node].empty()) {
        return walk;
    }
    
    walk.push_back(start_node);
    
    // If walk_length is 1, just return the start node
    if (walk_length == 1) {
        return walk;
    }
    
    // Choose second node uniformly at random
    const auto& neighbors = graph[start_node];
    if (neighbors.empty()) {
        return walk;
    }
    
    std::uniform_int_distribution<u32> dist(0, neighbors.size() - 1);
    u32 prev_node = start_node;
    u32 curr_node = neighbors[dist(rng)];
    walk.push_back(curr_node);
    
    // Continue the walk with biased transitions
    for (u32 i = 2; i < walk_length; ++i) {
        const auto& curr_neighbors = graph[curr_node];
        if (curr_neighbors.empty()) {
            break;
        }
        
        // Calculate transition probabilities
        std::vector<double> probs;
        probs.reserve(curr_neighbors.size());
        double sum_probs = 0.0;
        
        for (u32 next : curr_neighbors) {
            double prob = GetTransitionProbability(prev_node, curr_node, next);
            probs.push_back(prob);
            sum_probs += prob;
        }
        
        // Normalize probabilities
        if (sum_probs > 0.0) {
            for (double& prob : probs) {
                prob /= sum_probs;
            }
        } else {
            // Uniform distribution if all probabilities are zero
            double uniform_prob = 1.0 / curr_neighbors.size();
            for (double& prob : probs) {
                prob = uniform_prob;
            }
        }
        
        // Sample next node based on probabilities
        std::uniform_real_distribution<double> unif_dist(0.0, 1.0);
        double rand_val = unif_dist(rng);
        double cumsum = 0.0;
        u32 next_node = curr_neighbors[0];
        
        for (size_t j = 0; j < curr_neighbors.size(); ++j) {
            cumsum += probs[j];
            if (rand_val <= cumsum) {
                next_node = curr_neighbors[j];
                break;
            }
        }
        
        prev_node = curr_node;
        curr_node = next_node;
        walk.push_back(curr_node);
    }
    
    return walk;
}

// Get transition probability for Node2Vec biased random walk
double ExploredGraph::GetTransitionProbability(u32 prev_node, u32 curr_node, u32 next_node) {
    if (next_node == prev_node) {
        // Return to previous node: 1/p
        return 1.0 / p;
    } else {
        // Check if next_node is a neighbor of prev_node
        const auto& prev_neighbors = graph[prev_node];
        bool is_neighbor = std::find(prev_neighbors.begin(), prev_neighbors.end(), next_node) 
                          != prev_neighbors.end();
        
        if (is_neighbor) {
            // Common neighbor: 1 (normal step)
            return 1.0;
        } else {
            // Not a neighbor: 1/q (explore further)
            return 1.0 / q;
        }
    }
}

// Train embeddings using Skip-gram on a walk
// Uses negative sampling: for each positive (context) sample, samples negative nodes
void ExploredGraph::TrainSkipGram(const std::vector<u32>& walk) {
    if (walk.size() < 2) {
        return;
    }
    
    // Collect all nodes in walk to exclude from negative sampling
    // This ensures negative samples are truly negative (not in the walk at all)
    std::unordered_set<u32> walk_nodes(walk.begin(), walk.end());
    
    // Collect all available nodes for negative sampling (excluding walk nodes)
    std::vector<u32> candidate_negative_nodes;
    candidate_negative_nodes.reserve(embeddings.size());
    std::vector<u32> all_nodes_fallback;
    all_nodes_fallback.reserve(embeddings.size());
    
    for (const auto& emb_entry : embeddings) {
        u32 node = emb_entry.first;
        all_nodes_fallback.push_back(node);
        // Only include nodes that are NOT in the current walk
        if (walk_nodes.find(node) == walk_nodes.end()) {
            candidate_negative_nodes.push_back(node);
        }
    }
    
    // Use candidate_negative_nodes if available, otherwise fallback to all_nodes_fallback
    // This can happen early in training when graph is small
    const std::vector<u32>* negative_candidates = candidate_negative_nodes.empty() 
        ? &all_nodes_fallback 
        : &candidate_negative_nodes;
    
    if (negative_candidates->empty()) {
        return;
    }
    
    // Number of negative samples per positive sample (standard: 5)
    const u32 num_negative_samples = 5;
    std::uniform_int_distribution<u32> neg_dist(0, negative_candidates->size() - 1);
    
    // For each node in the walk, predict its context (neighbors within window)
    for (size_t i = 0; i < walk.size(); ++i) {
        u32 center = walk[i];
        if (!embeddings.count(center)) {
            continue;
        }
        
        Embedding& center_emb = embeddings[center];
        
        // Consider nodes within window_size on both sides
        int start = std::max(0, (int)i - (int)window_size);
        int end = std::min((int)walk.size(), (int)i + (int)window_size + 1);
        
        for (int j = start; j < end; ++j) {
            if (j == (int)i) continue; // Skip the center node itself
            
            u32 context = walk[j];
            if (!embeddings.count(context)) {
                continue;
            }
            
            Embedding& context_emb = embeddings[context];
            
            // === POSITIVE SAMPLE ===
            // Compute dot product (similarity)
            double dot_product = 0.0;
            for (u32 d = 0; d < embedding_dim; ++d) {
                dot_product += center_emb[d] * context_emb[d];
            }
            
            // Sigmoid activation
            double sigmoid = 1.0 / (1.0 + std::exp(-dot_product));
            
            // Gradient for positive sample: maximize P(context|center)
            // Loss = -log(sigmoid(dot_product))
            // dLoss/dcenter = -(1 - sigmoid) * context_emb
            // dLoss/dcontext = -(1 - sigmoid) * center_emb
            // Update: param += learning_rate * (1 - sigmoid) * other_emb (gradient ascent on log-likelihood)
            double pos_gradient = (1.0 - sigmoid) * learning_rate;
            
            // Update embeddings for positive sample
            for (u32 d = 0; d < embedding_dim; ++d) {
                double center_grad = pos_gradient * context_emb[d];
                double context_grad = pos_gradient * center_emb[d];
                
                center_emb[d] += center_grad;
                context_emb[d] += context_grad;
            }
            
            // === NEGATIVE SAMPLES ===
            // Sample negative nodes (not in walk) and minimize their similarity
            for (u32 neg = 0; neg < num_negative_samples; ++neg) {
                // Sample a random node from negative candidates (excludes walk nodes)
                u32 negative_node = (*negative_candidates)[neg_dist(rng)];
                
                // Skip if it's the center or context node (safety check)
                if (negative_node == center || negative_node == context) {
                    continue;
                }
                
                if (!embeddings.count(negative_node)) {
                    continue;
                }
                
                Embedding& negative_emb = embeddings[negative_node];
                
                // Compute dot product with negative sample
                double neg_dot_product = 0.0;
                for (u32 d = 0; d < embedding_dim; ++d) {
                    neg_dot_product += center_emb[d] * negative_emb[d];
                }
                
                // Sigmoid activation
                double neg_sigmoid = 1.0 / (1.0 + std::exp(-neg_dot_product));
                
                // Gradient for negative sample: minimize P(negative|center)
                // Loss = -log(1 - sigmoid(dot_product)) = -log(sigmoid(-dot_product))
                // dLoss/dcenter = sigmoid * negative_emb
                // dLoss/dnegative = sigmoid * center_emb
                // Update: param -= learning_rate * sigmoid * other_emb (gradient descent)
                double neg_gradient = -neg_sigmoid * learning_rate;
                
                // Update embeddings for negative sample
                for (u32 d = 0; d < embedding_dim; ++d) {
                    double center_grad = neg_gradient * negative_emb[d];
                    double negative_grad = neg_gradient * center_emb[d];
                    
                    center_emb[d] += center_grad;
                    negative_emb[d] += negative_grad;
                }
            }
        }
    }
}

// Compute mean embedding of a trace (walk)
// Returns the average embedding vector of all nodes in the trace
Embedding ExploredGraph::MeanEmbedding(const ExecTrace& trace) const {
    // Enforce invariant: trace must be non-empty
    if (trace.empty()) {
        throw std::logic_error("MeanEmbedding: trace cannot be empty");
    }
    
    std::lock_guard<std::mutex> lock(graph_mutex);
    
    Embedding result(embedding_dim, 0.0);
    u32 node_count = 0;

    // Sum embeddings of all nodes in the trace that have embeddings
    for (u32 node : trace) {
        if (embeddings.count(node)) {
            const auto& emb = embeddings.at(node);
            for (u32 i = 0; i < embedding_dim; ++i) {
                result[i] += emb[i];
            }
            node_count++;
        }
    }

    // Compute mean - only divide by nodes that actually have embeddings
    // If no nodes have embeddings, return zero embedding
    if (node_count > 0) {
        for (u32 i = 0; i < embedding_dim; ++i) {
            result[i] /= node_count;
        }
    }
    // Otherwise result is already zero-initialized
    
    return result;
}

// Compute L2 distance between two embeddings
// Returns the Euclidean distance in embedding space
double ExploredGraph::EmbeddingDistance(const Embedding& emb1, const Embedding& emb2) const {
    // Use the minimum of actual sizes and embedding_dim to handle edge cases
    u32 dim = std::min(embedding_dim, std::min(static_cast<u32>(emb1.size()), static_cast<u32>(emb2.size())));
    
    double dist_sq = 0.0;
    for (u32 d = 0; d < dim; ++d) {
        double diff = emb2[d] - emb1[d];
        dist_sq += diff * diff;
    }
    
    // Handle case where embeddings have different sizes
    // Add contribution from extra dimensions (treat missing as zero)
    if (emb1.size() > dim) {
        for (u32 d = dim; d < emb1.size() && d < embedding_dim; ++d) {
            dist_sq += emb1[d] * emb1[d];
        }
    }
    if (emb2.size() > dim) {
        for (u32 d = dim; d < emb2.size() && d < embedding_dim; ++d) {
            dist_sq += emb2[d] * emb2[d];
        }
    }
    
    return std::sqrt(dist_sq);
}

// Get distance between two nodes in embedding space
// Returns the Euclidean distance between the embeddings of the two nodes
double ExploredGraph::GetNodeDistance(u32 node1, u32 node2) const {
    Embedding emb1 = GetNodeEmbedding(node1);
    Embedding emb2 = GetNodeEmbedding(node2);
    return EmbeddingDistance(emb1, emb2);
}

// Get distance between a node and the origin (zero embedding)
// Returns the Euclidean distance from the node's embedding to zero
double ExploredGraph::GetNodeDistanceWithOrigin(u32 node) const {
    Embedding emb = GetNodeEmbedding(node);
    return EmbeddingDistance(emb, ZERO_EMBEDDING);
}

// Copy graph data (without mutex) - for serialization/crash info
void ExploredGraph::CopyGraphData(const ExploredGraph& other) {
    std::lock_guard<std::mutex> lock_this(graph_mutex);
    std::lock_guard<std::mutex> lock_other(other.graph_mutex);
    graph = other.graph;
    embeddings = other.embeddings;
    embedding_dim = other.embedding_dim;
    p = other.p;
    q = other.q;
    walk_length = other.walk_length;
    num_walks = other.num_walks;
    window_size = other.window_size;
    learning_rate = other.learning_rate;
    ZERO_EMBEDDING = other.ZERO_EMBEDDING;
    // Note: rng is not copied (new instance will have its own)
}

