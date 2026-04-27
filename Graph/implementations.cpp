#include <iostream>
#include <string>
#include "AirportData.hpp"
#include "WeightedGraph.hpp"
#include "MinHeap.hpp"

using namespace std;

void strToUpper(string &s)
{
    string upperStr;

    for (char &c : s)
    {
        c = toupper(c);
    }
}

void shortestPortToPort(WeightedGraph &adGraph)
{
    string origin;
    string destination;

    cout << "\nEnter origin airport code: ";
    cin >> origin;

    cout << "Enter destination airport code: ";
    cin >> destination;

    AirportData src;
    AirportData dest;

    strToUpper(origin);
    strToUpper(destination);

    src.origin = origin;
    dest.origin = destination;

    adGraph.shortestPath(src, dest);
}

void shortestPathsToStateCommand(WeightedGraph &adGraph)
{
    string origin;
    string state;

    cout << "\nEnter origin airport code: ";
    cin >> origin;

    cout << "Enter destination state abbreviation: ";
    cin >> state;

    strToUpper(origin);
    strToUpper(state);

    AirportData src;
    src.origin = origin;

    adGraph.shortestPathsToState(src, state);
}

void shortestPathWithStopsCommand(WeightedGraph &adGraph)
{
    string origin;
    string destination;
    int stops;

    cout << "\nEnter origin airport code: ";
    cin >> origin;

    cout << "Enter destination airport code: ";
    cin >> destination;

    cout << "Enter number of stops: ";
    cin >> stops;

    strToUpper(origin);
    strToUpper(destination);

    AirportData src;
    AirportData dest;

    src.origin = origin;
    dest.origin = destination;

    adGraph.shortestPathWithStops(src, dest, stops);
}

WeightedGraph createUndirected(WeightedGraph &adGraph)
{
    WeightedGraph uAdGraph;

    uAdGraph.vertices = adGraph.vertices;
    uAdGraph.edges.resize(adGraph.vertices.size());

    std::vector<std::vector<bool>> visitedMat(adGraph.vertices.size(), std::vector<bool>(adGraph.vertices.size(), false));

    for (int u = 0; u < adGraph.edges.size(); u++)
    {
        for (const Edge &edge : adGraph.edges[u])
        {
            int v = edge.to;

            if (visitedMat[u][v] || visitedMat[v][u])
                continue;

            visitedMat[u][v] = true;
            visitedMat[v][u] = true;

            int costUV = edge.cost;
            int costVU = -1;

            // Chk reversed edges also
            for (const Edge &revE : adGraph.edges[v])
            {
                if (revE.to == u)
                {
                    costVU = revE.cost;
                    break;
                }
            }

            int finCost;
            if (costVU == -1)
            {
                finCost = costUV;
            }
            else
            {
                finCost = costUV < costVU ? costUV : costVU;
            }

            uAdGraph.edges[u].push_back(Edge(v, 0, finCost));
            uAdGraph.edges[v].push_back(Edge(u, 0, finCost));
        }
    }

    return uAdGraph;
}

class HeapEdge
{
public:
    int from;
    int to;
    int cost;

    HeapEdge(int f, int t, int c) : from(f), to(t), cost(c)
    {
    }

    bool operator<(const HeapEdge &other) const
    {
        return cost < other.cost;
    }
};

void mstPrims(WeightedGraph &adGraph)
{
    int vertLen = adGraph.vertices.size();

    if (!adGraph.isConnected())
    {
        cout << "Graph isn't connected; Can't form MST" << endl;
        return;
    }

    vector<bool> visited(vertLen, false);
    vector<HeapEdge> edges;
    MinHeap<HeapEdge> heap;
    int totalCost = 0;

    visited[0] = true;
    for (const Edge &edge : adGraph.edges[0])
    {
        heap.insert(HeapEdge(0, edge.to, edge.cost));
    }

    while (!heap.empty() && edges.size() < vertLen - 1)
    {
        HeapEdge curr = heap.deleteMin();

        if (visited[curr.to])
        {
            continue;
        }

        visited[curr.to] = true;
        edges.push_back(curr);
        totalCost += curr.cost;

        for (const Edge &edge : adGraph.edges[curr.to])
        {
            if (!visited[edge.to])
            {
                heap.insert(HeapEdge(0, edge.to, edge.cost));
            }
        }
    }

    for (const HeapEdge &edge : edges)
    {
        cout << adGraph.vertices[edge.from] << " - " << adGraph.vertices[edge.to] << " cost: " << edge.cost << endl;
    }

    cout << "Total cost: " << totalCost << endl;
}

void msfKruskals(WeightedGraph adGraph)
{
    cout << "unimplemented" << endl;
}