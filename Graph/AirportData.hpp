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
public:
    string origin;
    string dst;

    string originCity;
    string originState;

    string dstCity;
    string dstState;

    int dist;
    int cost;

    AirportData()
    {
        dist = 0;
        cost = 0;
    }

    AirportData(string o, string d, string oC, string oS,
                string dC, string dS, int dis, int cos)
    {
        origin = o;
        dst = d;
        originCity = oC;
        originState = oS;
        dstCity = dC;
        dstState = dS;
        dist = dis;
        cost = cos;
    }

    bool operator==(const AirportData &other) const
    {
        return origin == other.origin;
    }

    friend ostream &operator<<(ostream &os, const AirportData &dt)
    {
        os << dt.origin;
        return os;
    }

    static string cleanCity(string city)
    {
        while (!city.empty() && city[0] == '"')
        {
            city.erase(0, 1);
        }

        while (!city.empty() && city[city.size() - 1] == '"')
        {
            city.pop_back();
        }

        return city;
    }

    static string getStateFromCity(string city)
    {
        int commaPos = city.find(',');

        if (commaPos == string::npos)
        {
            return "";
        }

        string state = city.substr(commaPos + 1);

        while (!state.empty() && state[0] == ' ')
        {
            state.erase(0, 1);
        }

        while (!state.empty() && state[state.size() - 1] == '"')
        {
            state.pop_back();
        }

        return state;
    }

    static vector<AirportData> load_file(string fName)
    {
        ifstream file(fName);
        string line;
        vector<AirportData> data;

        int lineCounter = 0;

        while (getline(file, line))
        {
            lineCounter++;

            if (lineCounter > 1)
            {
                stringstream ss(line);

                string tempOrigin;
                string tempDst;

                string originCityPart1;
                string originCityPart2;

                string dstCityPart1;
                string dstCityPart2;

                string tempOriginCity;
                string tempDstCity;

                string tempOriginState;
                string tempDstState;

                string temp;
                int tempDist = 0;
                int tempCost = 0;

                getline(ss, tempOrigin, ',');
                getline(ss, tempDst, ',');

                getline(ss, originCityPart1, ',');
                getline(ss, originCityPart2, ',');

                tempOriginCity = originCityPart1 + "," + originCityPart2;
                tempOriginCity = cleanCity(tempOriginCity);
                tempOriginState = getStateFromCity(tempOriginCity);

                getline(ss, dstCityPart1, ',');
                getline(ss, dstCityPart2, ',');

                tempDstCity = dstCityPart1 + "," + dstCityPart2;
                tempDstCity = cleanCity(tempDstCity);
                tempDstState = getStateFromCity(tempDstCity);

                getline(ss, temp, ',');
                if (!temp.empty())
                {
                    tempDist = stoi(temp);
                }

                getline(ss, temp, ',');
                if (!temp.empty())
                {
                    tempCost = stoi(temp);
                }

                data.push_back(AirportData(
                    tempOrigin,
                    tempDst,
                    tempOriginCity,
                    tempOriginState,
                    tempDstCity,
                    tempDstState,
                    tempDist,
                    tempCost));
            }
        }

        file.close();
        return data;
    }
};

#endif