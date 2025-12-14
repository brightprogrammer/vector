#include "loss.hh"
#include <cmath>
#include <stdexcept>

// Cosine similarity for embeddings (used in embedding-based loss)
double CosineSimilarity(const Embedding& tr1, const Embedding& tr2) {
    // max dimension
    u32 l = tr1.size() < tr2.size() ? tr2.size() : tr1.size();

    double dot = 0;
    double mag_y1 = 0;
    double mag_y2 = 0;
    
    for(u32 i = 0; i < l; i++) {
        double a = i < tr1.size() ? tr1[i] : 0;
        double b = i < tr2.size() ? tr2[i] : 0;

        dot += a*b;
        mag_y1 += a * a;
        mag_y2 += b * b;
    }

    if (mag_y1 == 0 || mag_y2 == 0) return 0.0;
    return dot/std::sqrt(mag_y1*mag_y2);
}

// Embedding-based loss
// Automatically updates graph and embeddings, then computes loss in embedding space
// Takes an ExploredGraph reference to operate on
double EmbeddingLoss(ExploredGraph& graph, const ExecTrace& forbidden_walk, const ExecTrace& walk) {
    // Enforce invariant: traces must be non-empty
    if (walk.empty()) {
        throw std::logic_error("EmbeddingLoss: walk trace cannot be empty");
    }
    if (forbidden_walk.empty()) {
        throw std::logic_error("EmbeddingLoss: forbidden_walk trace cannot be empty");
    }
    
    // Update graph with new traces (adds nodes and edges)
    graph.UpdateGraphFromTrace(walk);
    graph.UpdateGraphFromTrace(forbidden_walk);
    
    // Update embeddings for all nodes using Node2Vec
    // This trains embeddings to capture graph structure
    graph.UpdateEmbeddings();

    // Compute mean embeddings for both walks
    // Mean embedding represents the overall "direction" of the walk in embedding space
    Embedding emb_walk = graph.MeanEmbedding(walk);
    Embedding emb_forbidden = graph.MeanEmbedding(forbidden_walk);
    
    // Compute cosine similarity (ranges from -1 to 1)
    double similarity = CosineSimilarity(emb_walk, emb_forbidden);
    
    // Normalize to [0, 1] range for loss:
    // - Similar traces (similarity ≈ 1) → high loss (≈ 1.0)
    // - Different traces (similarity ≈ -1) → low loss (≈ 0.0)
    // - Orthogonal traces (similarity ≈ 0) → medium loss (≈ 0.5)
    // Formula: (similarity + 1) / 2 maps [-1, 1] to [0, 1]
    return (similarity + 1.0) / 2.0;
}

