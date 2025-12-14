#ifndef VECTOR_FUZZER_LOSS_HH
#define VECTOR_FUZZER_LOSS_HH

#include "types.hh"
#include "graph.hh"
#include <vector>

// Cosine similarity for embeddings (used in embedding-based loss)
double CosineSimilarity(const Embedding& tr1, const Embedding& tr2);

// Embedding-based loss
// Automatically updates graph and embeddings, then computes loss in embedding space
// Takes an ExploredGraph reference to operate on
double EmbeddingLoss(ExploredGraph& graph, const ExecTrace& forbidden_walk, const ExecTrace& walk);

#endif // VECTOR_FUZZER_LOSS_HH
