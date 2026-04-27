#include <fstream>
#include "WeightedGraph.hpp"
#include <string>
#include <vector>
#include "AirportData.hpp"
#include <iostream>

WeightedGraph initGraph(vector<AirportData> &airports);

void strToUpper(std::string &s);
void shortestPortToPort(WeightedGraph &adGraph);
void shortestPathsToStateCommand(WeightedGraph &adGraph);
void shortestPathWithStopsCommand(WeightedGraph &adGraph);
WeightedGraph createUndirected(WeightedGraph &adGraph);

int main(void)
{
    cout << "Project 3 Flight optimization" << endl;

    vector<AirportData> airports = AirportData::load_file();

    WeightedGraph adGraph = initGraph(airports);
    bool isUnd = false;

    string command;

    while (command != "exit")
    {
        cout << "Enter command (help for commands):";

        cin >> command;

        if (command == "help")
        {
            cout << "p2p: (Finds the shortest distance path between an origin airport and destination airport)" << endl;
            cout << "state: (Finds shortest paths from an origin airport to all airports in a state)" << endl;
            cout << "stops: (Finds shortest path between airports with exactly N stops)" << endl;
            cout << "undirected: (Converts graph to an undirected graph and stores it for use, must use reset to reset to weighted graph)" << endl;
            cout << "reset: (Reinitialize the directional graph)" << endl;
            cout << "print1: (Prints the available airports for use)" << endl;
            cout << "print2: (Prints the available airports and their connections)" << endl;
            cout << "printd: (Writes graph debugging out to dbg_graph.dot)" << endl;
        }
        else if (command == "p2p")
        {
            shortestPortToPort(adGraph);
        }
        else if (command == "state")
        {
            shortestPathsToStateCommand(adGraph);
        }
        else if (command == "stops")
        {
            shortestPathWithStopsCommand(adGraph);
        }
        else if (command == "undirected")
        {
            if (isUnd)
            {
                cout << "Graph already undirected" << endl;

                continue;
            }

            adGraph = createUndirected(adGraph);
            isUnd = true;

            cout << "Created and stored undirected graph" << endl;
        }
        else if (command == "reset")
        {
            adGraph = initGraph(airports);
            isUnd = false;
        }
        else if (command == "print1")
        {
            for (int i = 0; i < adGraph.vertices.size(); i++)
            {
                cout << adGraph.vertices[i];

                if (i < adGraph.vertices.size() - 1)
                {
                    cout << ",";
                }
                else
                {
                    cout << endl;
                }
            }
        }
        else if (command == "print2")
        {
            adGraph.print();
        }
        else if (command == "printd")
        {
            ofstream out("dbg_graph.dot");

            out << (isUnd ? "" : "di") << "graph G {" << endl;

            for (int i = 0; i < adGraph.vertices.size(); i++)
            {
                for (int j = 0; j < adGraph.edges[i].size(); j++)
                {
                    out << "    "
                        << adGraph.vertices[i].origin
                        << (isUnd ? " -- " : " -> ")
                        << adGraph.vertices[adGraph.edges[i][j].to].origin
                        << ";" << endl;
                }
            }

            out << "}" << endl;

            out.close();

            cout << "Wrote contents to dbg_graph.dot" << endl;
        }
        else if (command != "exit")
        {
            cout << "Unknown command :(";
        }
    }

    return 0;
}

WeightedGraph initGraph(vector<AirportData> &airports)
{
    WeightedGraph adGraph;

    for (const AirportData &ad : airports)
    {
        if (adGraph.getVertexIndex(ad) == -1)
        {
            adGraph.insertVertex(ad);
        }
    }

    for (const AirportData &ad : airports)
    {
        for (const AirportData &adOther : airports)
        {
            if (ad.dst == adOther.origin)
            {
                adGraph.insertEdge(ad, adOther, ad.dist, ad.cost);
            }
        }
    }

    return adGraph;
}