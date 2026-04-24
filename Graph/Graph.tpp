#include "Graph.hpp"
#include "queue/QueueDLL.hpp"
#include <iostream>
#include <vector>
#include<queue>

template <typename T>
int Graph<T>::getVertexIndex(const T &value) const
{
    int i = 0;
    for (const auto &v : vertices)
    {
        if (v == value)
        {
            return i;
        }
        i++;
    }

    return -1; // No element
}

template <typename T>
void Graph<T>::insertVertex(const T &value)
{
    if (getVertexIndex(value) != -1)
    {
        std::cout << "insertVertex: vertex already exists\n";
        return;
    }
    vertices.push_back(value); // Add the new vertex
    std::vector<int> tmp;
    edges.push_back(tmp); // Empty list of neighbours for the new vertex
}

template <typename T>
void Graph<T>::insertEdge(const T &v1, const T &v2)
{
    int i1 = getVertexIndex(v1);
    int i2 = getVertexIndex(v2);
    if (i1 == -1 || i2 == -1)
    {
        std::cout << "insertEdge: incorrect vertices\n";
        return;
    }
    edges[i1].push_back(i2);
    if (i1 != i2)
    {
        edges[i2].push_back(i1);
    }
}

template <typename T>
void Graph<T>::print() const
{
    for (int i = 0; i < vertices.size(); i++)
    {
        std::cout << "{ " << vertices[i] << ": ";
        for (int j = 0; j < edges[i].size(); j++)
        {
            std::cout << vertices[edges[i][j]] << " ";
        }
        std::cout << "}\n";
    }
}

template <typename T>
bool Graph<T>::hasEdge(int i1, int i2) const
{
    if (i1 < 0 || i1 >= edges.size())
    {
        return false;
    }

    for (int i : edges[i1])
    {
        if (i == i2)
        {
            return true;
        }
    }

    return false;
}

template <typename T>
void Graph<T>::DFS() const
{
    if (vertices.empty())
    {
        return;
    }
    std::vector<bool> visited(vertices.size(), false);
    DFS(0, visited);
}

template <typename T>
void Graph<T>::DFS(int i, std::vector<bool> &visited) const
{
    visited[i] = true;
    std::cout << vertices[i] << " -> ";

    // Look through all the neighbours
    for (int j : edges[i])
    {
        if (!visited[j])
        {
            DFS(j, visited);
        }
    }
}

template <typename T>
void Graph<T>::BFS(int start) const
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
        for (int j : edges[cur])
        {
            if (!discovered[j])
            {
                where_to_go.enqueue(j);
                discovered[j] = true;
            }
        }
    }
}


template <typename T>
int Graph<T>::shortestPath(const T &src, const T &dest) const
{
    // Find indices
    int i_src = getVertexIndex(src);
    int i_dest = getVertexIndex(dest);

    // Check edge case
    if (i_src == -1 || i_dest == -1)
    {
        std::cout << "shortestPath: incorrect indices";
        return -1;
    }
    if (i_src == i_dest)
    {
        return 0;
    }
    // Create distances vector
    std::vector<int> distances(vertices.size()); // distances from source to all other nodes
    // Set initial distances
    for (int i = 0; i < distances.size(); i++)
    {
        distances[i] = (i == i_src) ? 0 : -1;
    }

    // Perform BFS and update distances
    QueueDLL<int> q;
    q.enqueue(i_src);

    while (!q.empty())
    {
        int cur = q.front();
        q.dequeue();

        // Check the neighbors of current node
        for (int i : edges[cur])
        {
            if (distances[i] == -1)
            {
                distances[i] = distances[cur] + 1;
                q.enqueue(i);
            }
            if (i == i_dest)
            {
                return distances[i];
            }
        }
    }

    return -1; // No path exists
}
