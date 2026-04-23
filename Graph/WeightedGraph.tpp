#include "WeightedGraph.hpp"
#include <iostream>

// Helper: Converts airport code string to index
template <typename T>
int WeightedGraph<T>::getVertexIndex(const T& vs) const {
    for (int i = 0; i < vertices.size(); ++i) {
        if (vertices[i] == vs) return i;
    }
    return -1; // Not found
}

// Inserts a new airport if it doesn't exist
template <typename T>
void WeightedGraph<T>::insertVertex(const T& v) {
    if (getVertexIndex(v) == -1) {
        vertices.push_back(v);
        edges.push_back(std::vector<Edge>());
    }
}

// Inserts a directed edge with both distance and cost
template <typename T>
void WeightedGraph<T>::insertEdge(const T& v1, const T& v2, int distance, int cost) {
    int idx1 = getVertexIndex(v1);
    int idx2 = getVertexIndex(v2);
    
    // Ensure vertices exist before adding edge
    if (idx1 != -1 && idx2 != -1) {
        edges[idx1].push_back(Edge(idx2, distance, cost));
    }
}
