#include <fstream>
#include "WeightedGraph.hpp"
#include <string>
#include <vector>
#include "AirportData.hpp"
#include <iostream>

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

    adGraph.print();

    string origin;
    string destination;

    cout << "\nEnter origin airport code: ";
    cin >> origin;

    cout << "Enter destination airport code: ";
    cin >> destination;

    AirportData src;
    AirportData dest;

    src.origin = origin;
    dest.origin = destination;

    adGraph.shortestPath(src, dest);

    cout << "\nFin\n";

    return 0;
}
