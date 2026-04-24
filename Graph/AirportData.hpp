#ifndef AIRPORTDATA_HPP
#define AIRPORTDATA_HPP

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class AirportData
{
private:
public:
    string origin;
    string dst;
    string originCity;
    string dstCity;
    int dist;
    int cost;

    AirportData(string o, string d, string oC, string dC, int dis, int cos) : origin(o), dst(d), originCity(oC), dstCity(dC), dist(dis), cost(cos)
    {
    }

    AirportData()
    {
    }

    bool operator==(const AirportData &other) const
    {
        return this->origin == other.origin;
    }

    friend ostream& operator<<(ostream& os, const AirportData& dt)
    {
        os << dt.origin;
        return os;
    }

    static vector<AirportData> load_file()
    {
        // nays habitat

        ifstream file("airports.csv");
        string line;
        string temp;
        string temporigin;
        string tempdst;
        string temporiginCity;
        string tempdstCity;
        int tempdist;
        int tempcost;
        vector<vector<string>> columns;

        vector<AirportData> data;

        int lineCounter = 0;
        while (getline(file, line))
        {
            lineCounter++;
            if (lineCounter > 1)
            {
                stringstream ss(line);

                // Parse strings
                getline(ss, temporigin, ',');
                getline(ss, tempdst, ',');
                getline(ss, temporiginCity, ',');
                getline(ss, tempdstCity, ',');

                //
                getline(ss, temp, ',');
                if (!temp.empty())
                    tempdist = stoi(temp);

                getline(ss, temp, ',');
                if (!temp.empty())
                    tempcost = stoi(temp);

                data.push_back(AirportData(temporigin, tempdst, temporiginCity, tempdstCity, tempdist, tempcost));
            }
        }
        file.close();

        return data;
    }
};

#endif