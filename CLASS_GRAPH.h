#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include <queue>
#include <vector>
#include <climits>
#include <algorithm>

class Graph {
private:
    int numVert;
    std::vector<std::vector<int>> AdjMatrix;
    std::vector<std::list<int>> AdjList;
public:
    Graph(std::ifstream& f) {
        f >> numVert;
        AdjMatrix.resize(numVert, std::vector<int>(numVert));
        AdjList.resize(numVert);
        for (int i = 0; i < numVert; i++) {
            for (int j = 0; j < numVert; j++) {
                f >> AdjMatrix[i][j];
                if (AdjMatrix[i][j] > 0) {
                    AdjList[i].push_back(j);
                }
            }
        }
    }
    void showMATRIX() {
        std::cout << "\nMATRIX VIEW:\n";
        for (int i = 0; i < numVert; i++) {
            for (int j = 0; j < numVert; j++) {
                std::cout << AdjMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    void showLIST() {
        std::cout << "\nLIST VIEW:\n";
        for (int i = 0; i < numVert; i++) {
            std::cout << i << " : ";
            for (int v : AdjList[i]) {
                std::cout << v << " ";
            }
            std::cout << std::endl;
        }
    }
    void BFSmatrix(int Vertex) {
        std::cout << "\nBFS MATRIX: ";
        std::vector<bool> visited(numVert, false);
        std::queue<int> queue;
        visited[Vertex] = true;
        queue.push(Vertex);
        while (!queue.empty()) {
            Vertex = queue.front();
            std::cout << Vertex << " ";
            queue.pop();
            for (int i = 0; i < numVert; i++) {
                if (AdjMatrix[Vertex][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    queue.push(i);
                }
            }
        }
    }
    void BFSlist(int Vertex) {
        std::cout << "\nBFS LIST: ";
        std::vector<bool> visited(numVert, false);
        std::queue<int> queue;
        visited[Vertex] = true;
        queue.push(Vertex);
        while (!queue.empty()) {
            Vertex = queue.front();
            std::cout << Vertex << " ";
            queue.pop();
            for (int v : AdjList[Vertex]) {
                if (!visited[v]) {
                    visited[v] = true;
                    queue.push(v);
                }
            }
        }
    }
    void DFS(int Vertex) {
        std::vector<bool> visited(numVert, false);
        DFSUtil(Vertex, visited);
    }
    void DFSUtil(int Vertex, std::vector<bool>& visited) {
        visited[Vertex] = true;
        std::cout << Vertex << " ";
        for (int v : AdjList[Vertex]) {
            if (!visited[v]) {
                DFSUtil(v, visited);
            }
        }
    }
    void Dijkstra(int start) {
        std::vector<int> dist(numVert, std::numeric_limits<int>::max());
        dist[start] = 0;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        pq.push({ 0, start });

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (int v : AdjList[u]) {
                int weight = AdjMatrix[u][v];
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push({ dist[v], v });
                }
            }
        }
        std::cout << "\nDijkstra shortest paths from vertex " << start << ":\n";
        for (int i = 0; i < numVert; ++i) {
            std::cout << start << " to " << i << " : " << dist[i] << "\n";
        }
    }
    void FloydWarshall() {
        std::vector<std::vector<int>> dist = AdjMatrix;
        for (int k = 0; k < numVert; ++k) {
            for (int i = 0; i < numVert; ++i) {
                for (int j = 0; j < numVert; ++j) {
                    if (dist[i][k] != std::numeric_limits<int>::max() && dist[k][j] != std::numeric_limits<int>::max() && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        std::cout << "\nFloyd-Warshall shortest paths between all pairs of vertices:\n";
        for (int i = 0; i < numVert; ++i) {
            for (int j = 0; j < numVert; ++j) {
                if (dist[i][j] == std::numeric_limits<int>::max()) {
                    std::cout << i << " to " << j << " : No path\n";
                }
                else {
                    std::cout << i << " to " << j << " : " << dist[i][j] << "\n";
                }
            }
        }
    }
    void connectedComponents() {
        std::vector<bool> visited(numVert, false);
        int components = 0;
        for (int i = 0; i < numVert; ++i) {
            if (!visited[i]) {
                components++;
                std::cout << "Connected component " << components << ": ";
                BFSlistConnected(i, visited);
                std::cout << std::endl;
            }
        }
        std::cout << "Total connected components: " << components << std::endl;
    }
    void BFSlistConnected(int Vertex, std::vector<bool>& visited) {
        std::queue<int> queue;
        visited[Vertex] = true;
        queue.push(Vertex);
        while (!queue.empty()) {
            Vertex = queue.front();
            std::cout << Vertex << " ";
            queue.pop();
            for (int v : AdjList[Vertex]) {
                if (!visited[v]) {
                    visited[v] = true;
                    queue.push(v);
                }
            }
        }
    }
    void shortestPathBFS(int start) {
        std::vector<int> dist(numVert, -1);
        std::queue<int> queue;
        dist[start] = 0;
        queue.push(start);
        while (!queue.empty()) {
            int v = queue.front();
            queue.pop();
            for (int u : AdjList[v]) {
                if (dist[u] == -1) {
                    dist[u] = dist[v] + 1;
                    queue.push(u);
                }
            }
        }
        std::cout << "\nShortest distances from vertex " << start << " using BFS:\n";
        for (int i = 0; i < numVert; ++i) {
            std::cout << start << " to " << i << " : " << dist[i] << "\n";
        }
    }
    void Prim() {
        std::vector<int> parent(numVert, -1);
        std::vector<int> key(numVert, INT_MAX);
        std::vector<bool> inMST(numVert, false);
        key[0] = 0;
        for (int count = 0; count < numVert - 1; ++count) {
            int minKey = INT_MAX, minIndex = -1;
            for (int v = 0; v < numVert; ++v) {
                if (!inMST[v] && key[v] < minKey) {
                    minKey = key[v];
                    minIndex = v;
                }
            }
            inMST[minIndex] = true;
            for (int u : AdjList[minIndex]) {
                int neighbor = u;
                int weight = AdjMatrix[minIndex][neighbor];
                if (!inMST[neighbor] && weight < key[neighbor]) {
                    parent[neighbor] = minIndex;
                    key[neighbor] = weight;
                }
            }
        }
        std::cout << "\nPrim's Minimum Spanning Tree:\n";
        for (int i = 1; i < numVert; i++) {
            std::cout << parent[i] << " - " << i << " : " << AdjMatrix[i][parent[i]] << "\n";
        }
    }
    void Kruskal() {
        std::vector<std::pair<int, std::pair<int, int>>> edges;
        for (int u = 0; u < numVert; ++u) {
            for (int v : AdjList[u]) {
                int weight = AdjMatrix[u][v];
                edges.push_back({ weight, {u, v} });
            }
        }
        std::sort(edges.begin(), edges.end());
        std::vector<int> parent(numVert);
        for (int i = 0; i < numVert; ++i) {
            parent[i] = i;
        }
        int cost = 0;
        std::vector<std::pair<int, int>> result;
        for (const auto& edge : edges) {
            int weight = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;

            int setU = Find(u, parent);
            int setV = Find(v, parent);

            if (setU != setV) {
                cost += weight;
                result.push_back({ u, v });
                Union(setU, setV, parent);
            }
        }
        std::cout << "\nKruskal's Minimum Spanning Tree:\n";
        for (const auto& edge : result) {
            std::cout << edge.first << " - " << edge.second << " : " << AdjMatrix[edge.first][edge.second] << "\n";
        }
    }
private:
    int Find(int v, std::vector<int>& parent) {
        if (parent[v] == v) {
            return v;
        }
        return Find(parent[v], parent);
    }
    void Union(int u, int v, std::vector<int>& parent) {
        parent[u] = v;
    }
};
