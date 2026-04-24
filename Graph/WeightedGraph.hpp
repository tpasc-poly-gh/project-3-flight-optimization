#ifndef WEIGHTEDGRAPH_HPP
#define WEIGHTEDGRAPH_HPP
#include <vector>
#include "AirportData.hpp"


class WeightedGraph {
public:

    void insertVertex(const AirportData& v);
    void insertEdge(const AirportData& v1, const AirportData& v2);
    void print() const;

    void DFS() const;
    void BFS(int start = 0) const;
    int shortestPath(const AirportData& src, const AirportData& dest) const;
    bool isConnected() const;


private:
    std::vector<AirportData> vertices; 
    std::vector<std::vector<int>> edges; 

    
    int getVertexIndex(const AirportData& vs) const;

    bool hasEdge(int i1, int i2) const;
    void DFS(int i, std::vector<bool>& visited) const;
};

#include "WeightedGraph.tpp"

#endif