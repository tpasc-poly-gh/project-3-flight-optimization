#include <fstream>
#include "Graph.hpp"
#include <string>
#include <vector>
#include "AirportData.cpp"


int main(void) {
    Graph<AirportData> adGraph;

    vector<AirportData> airports = AirportData::load_file();

    for (const AirportData& ad : airports) {
        adGraph.insertVertex(ad);
    }

    for (const AirportData& ad : airports) {
        for (const AirportData& adOther : airports) {
            if (ad.dst == adOther.dst) {
                adGraph.insertEdge(ad, adOther);
            }
        }
    }
    

    return 0;
}
