
#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
template <typename T>
class Graph {
public:
void insertVertex(const T& value);
void insertEdge(const T& v1, const T& v2);
void print() const;
private:
std::vector<T> vertices;
std::vector<std::vector<int>> edges;
int getVertexIndex(const T& value) const;
};
#include "Graph.tpp"
#endif
