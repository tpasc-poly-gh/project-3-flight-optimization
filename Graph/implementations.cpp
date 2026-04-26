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

void shortestPortToPort(WeightedGraph adGraph)
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