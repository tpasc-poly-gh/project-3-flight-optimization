// #include "WeightedGraph.hpp"
// #include <string>
// #include <iostream>
// #include <fstream>
// #include <sstream>

// int main() {
//     WeightedGraph<std::string> graph;
//     std::ifstream file("airports.csv");
//     std::string line, origin, dest, oCity, dCity, distStr, costStr;

//     // Skip the header line
//     std::getline(file, line);

//     while (std::getline(file, line)) {
//         std::stringstream ss(line);
//         std::getline(ss, origin, ',');
//         std::getline(ss, dest, ',');
//         // ... parse city names ...
//         std::getline(ss, distStr, ',');
//         std::getline(ss, costStr, ',');

//         graph.insertVertex(origin);
//         graph.insertVertex(dest);
//         graph.insertEdge(origin, dest, std::stoi(distStr), std::stoi(costStr));
//     }
//     return 0;
// }