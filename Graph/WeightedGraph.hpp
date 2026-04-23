#ifndef WEIGHTEDGRAPH_HPP
#define WEIGHTEDGRAPH_HPP
#include <vector>

class Edge
{
    public:
        int neighbor;
        int distance;
        int cost;

        Edge(int n, int d, int c) : neighbor(n), distance(d), cost(c) { }

    private:

};

template <typename T>
class WeightedGraph {
public:

    void insertVertex(const T& v);
    void insertEdge(const T& v1, const T& v2, int distance = 1, int cost = 1);
    void print() const;

    int shortestPath(const T& src, const T& dest) const;

private:
    std::vector<T> vertices; 
    std::vector<std::vector<Edge>> edges; 

    
    int getVertexIndex(const T& vs) const;

    bool hasEdge(int i1, int i2) const; 
};

#include "WeightedGraph.tpp"

#endif