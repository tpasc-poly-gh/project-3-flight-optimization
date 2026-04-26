#ifndef WEIGHTEDGRAPH_HPP
#define WEIGHTEDGRAPH_HPP
#include <vector>
#include "AirportData.hpp"

class Edge
{
public:
    int to;
    int distance;
    int cost;
    Edge(int t, int d, int c) : to(t), distance(d), cost(c) {}
};

class PQNode
{
    int distance;
    int index;

    // Overload the '>' operator so the heap knows how to compare nodes
    bool operator>(const PQNode &other) const
    {
        return distance > other.distance;
    }
};

class WeightedGraph
{
public:
    std::vector<AirportData> vertices;
    std::vector<std::vector<Edge>> edges;
    void insertVertex(const AirportData &v);
    void insertEdge(const AirportData &v1, const AirportData &v2, int dist, int cost);
    void print() const;

    void DFS() const;
    void BFS(int start = 0) const;
    int shortestPath(const AirportData &src, const AirportData &dest) const;
    bool isConnected() const;
    int getVertexIndex(const AirportData &vs) const;

private:
    bool hasEdge(int i1, int i2) const;
    void DFS(int i, std::vector<bool> &visited) const;
};

template <typename T>
class PriorityQueue
{
private:
    std::vector<T> heap;

    void bubbleUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (heap[index] > heap[parent])
                break; // For a min-heap
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void bubbleDown(int index)
    {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heap.size() && heap[left] < heap[smallest])
            smallest = left;
        if (right < heap.size() && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != index)
        {
            std::swap(heap[index], heap[smallest]);
            bubbleDown(smallest);
        }
    }

public:
    void push(T val)
    {
        heap.push_back(val);
        bubbleUp(heap.size() - 1);
    }

    void pop()
    {
        heap[0] = heap.back();
        heap.pop_back();
        bubbleDown(0);
    }

    T top() const { return heap[0]; }
    bool empty() const { return heap.empty(); }
};

#include "WeightedGraph.tpp"

#endif