#include <fstream>
#include "WeightedGraph.hpp"
#include <string>
#include <vector>
#include "AirportData.hpp"
#include <iostream>
#include "implementations.cpp"

int main(void)
{
    cout << "Project 3 Flight optimization" << endl;

    WeightedGraph adGraph;

    vector<AirportData> airports = AirportData::load_file();

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

    string command;

    while (command != "exit")
    {
        cout << "Enter command (help for commands):";

        cin >> command;

        if (command == "help")
        {
            cout << "print1: (Prints the available airports for use)" << endl;
            cout << "print2: (Prints the available airports and their connections)" << endl;
            cout << "p2p: (Finds the shortest distance path between an origin airport and destination airport)" << endl;
        }
        else if (command == "p2p")
        {
            shortestPortToPort(adGraph);
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
    }

    return 0;
}
