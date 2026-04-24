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
        adGraph.insertVertex(ad);
    }

    for (const AirportData &ad : airports)
    {
        for (const AirportData &adOther : airports)
        {
            if (ad.dst == adOther.dst)
            {
                adGraph.insertEdge(ad, adOther);
            }
        }
    }

    adGraph.print();

    cout << "Fin";

    return 0;
}
