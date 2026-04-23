#include "Graph.hpp"
#include <string>

int main(void) {
    Graph<std::string> knowledge;

    knowledge.insertVertex("A");
    knowledge.insertVertex("B");
    knowledge.insertVertex("C");
    knowledge.insertVertex("D");
    knowledge.insertVertex("E");
    knowledge.insertVertex("F");
    knowledge.insertVertex("G");
    knowledge.insertVertex("S");
    knowledge.insertVertex("H");

    knowledge.insertEdge("A", "B");
    knowledge.insertEdge("A", "S");
    knowledge.insertEdge("C", "S");
    knowledge.insertEdge("G", "S");
    knowledge.insertEdge("C", "F");
    knowledge.insertEdge("C", "E");
    knowledge.insertEdge("C", "D");
    knowledge.insertEdge("E", "H");
    knowledge.insertEdge("G", "H");
    knowledge.insertEdge("G", "F");
    

    knowledge.print();
    knowledge.DFS();

    // TODO
    // 1. Create a disconnected Graph
    // 2. Update DFS to traverse all the nodes of this graph


    return 0;
}