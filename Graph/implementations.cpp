#include <iostream>
#include <string>
#include "AirportData.hpp"
#include "WeightedGraph.hpp"

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
                if (costUV < costVU)
                {
                    finCost = costUV;
                }
                else
                {
                    finCost = costVU;
                }
            }

            uAdGraph.edges[u].push_back(Edge(v, 0, finCost));
            uAdGraph.edges[v].push_back(Edge(u, 0, finCost));
        }
    }

    return uAdGraph;
}