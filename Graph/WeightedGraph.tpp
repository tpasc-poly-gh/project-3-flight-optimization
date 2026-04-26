#include "WeightedGraph.hpp"
#include <iostream>
#include "queue/QueueDLL.hpp"


void WeightedGraph::insertVertex(const AirportData &v)
{
    if (getVertexIndex(v) != -1)
    {
        std::cout << "insertVertex: vertex already exist\n";
        return;
    }

    vertices.push_back(v);
    std::vector<Edge> tmp; 
    edges.push_back(tmp); 
}

void WeightedGraph::insertEdge(const AirportData &v1, const AirportData &v2, int dist, int cost)
{
    int i1 = getVertexIndex(v1);
    int i2 = getVertexIndex(v2);

    if (i1 != -1 && i2 != -1 && !hasEdge(i1, i2)) 
    {
        edges[i1].push_back(Edge(i2, dist, cost));
    }

    if (i1 == -1 || i2 == -1)
    {
        std::cout << "insertEdge: incorrect vertices\n";
        return;
    }

}

int WeightedGraph::getVertexIndex(const AirportData &ver) const
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i] == ver)
        {
            return i;
        }
    }

    return -1;
}


void WeightedGraph::print() const
{
    for (int i = 0; i < vertices.size(); i++)
    {
        std::cout << "{ " << vertices[i].origin << ": ";
        for (int j = 0; j < edges[i].size(); j++)
        {
            std::cout << vertices[edges[i][j].to].origin << ' ';
        }
        std::cout << " }\n";
    }
}

bool WeightedGraph::hasEdge(int i1, int i2) const
{
    if (i1 < 0 || i1 >= edges.size())
    {
        return false;
    }

    for (const auto& edge : edges[i1])
    {
        if (edge.to == i2)
        {
            return true;
        }
    }

    return false;
}

void WeightedGraph::DFS() const
{
    if (vertices.empty())
    {
        return;
    }
    std::vector<bool> visited(vertices.size(), false);
    DFS(0, visited);
}

void WeightedGraph::DFS(int i, std::vector<bool> &visited) const
{
    visited[i] = true;
    std::cout << vertices[i].origin << " -> ";

    // Look through all the neighbours
    for (const auto& edge : edges[i])
    {
        if (!visited[edge.to])
        {
            DFS(edge.to, visited);
        }
    }
}

void WeightedGraph::BFS(int start) const
{
    if (vertices.empty() || start < 0 || start >= vertices.size())
    {
        return;
    }

    std::vector<bool> discovered(vertices.size(), false);
    QueueDLL<int> where_to_go;

    where_to_go.enqueue(start);
    discovered[start] = true;

    while (!where_to_go.empty())
    {
        int cur = where_to_go.front();
        std::cout << vertices[cur];
        where_to_go.dequeue();

        // Explore the neighbors
        for (const auto& edge : edges[cur])
        {
            if (!discovered[edge.to])
            {
                where_to_go.enqueue(edge.to);
                discovered[edge.to] = true;
            }
        }
    }
}

int WeightedGraph::shortestPath(const AirportData &src, const AirportData &dest) const
{
    int i_src = getVertexIndex(src);
    int i_dest = getVertexIndex(dest);

    if (i_src == -1 || i_dest == -1)
    {
        std::cout << "shortestPath: incorrect airport(s)\n";
        return -1;
    }

    const int INF = 2147483647;
    std::vector<int> distances(vertices.size(), INF);
    std::vector<int> previous(vertices.size(), -1);

    distances[i_src] = 0;

    PriorityQueue<std::pair<int, int>> pq;
    pq.push({0, i_src});

    while (!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > distances[u]) continue;

        for (const auto& edge : edges[u])
        {
            if (distances[u] != INF && distances[u] + edge.distance < distances[edge.to])
            {
                distances[edge.to] = distances[u] + edge.distance;
                previous[edge.to] = u;
                pq.push({distances[edge.to], edge.to});
            }
        }
    }

    if (distances[i_dest] == INF)
    {
        std::cout << "No path exists from " << src.origin << " to " << dest.origin << ".\n";
        return -1;
    }

    std::vector<int> path;
    for (int at = i_dest; at != -1; at = previous[at])
    {
        path.push_back(at);
    }

    std::cout << "Shortest path by distance: ";
    for (int i = path.size() - 1; i >= 0; i--)
    {
        std::cout << vertices[path[i]].origin;
        if (i != 0) std::cout << " -> ";
    }

    std::cout << "\nTotal distance: " << distances[i_dest] << "\n";

    return distances[i_dest];
}

bool WeightedGraph::isConnected() const {
    return true;
}
