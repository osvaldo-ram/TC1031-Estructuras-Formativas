#ifndef Graph_H_
#define Graph_H_

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

class Graph {
private:
    int edgesList;
    int edgesMat;
    int nodes;
    vector<int> *adjList;
    int *adjMatrix;

public:
    Graph(int);
    Graph();
    void addEdgeAdjList(int, int);
    void addEdgeAdjMatrix(int, int);
    string printAdjList();
    string printAdjMat();
    string DFS(int, int);
    string BFS(int, int);
    void sortAdjList();
    void loadGraphList(string, int);
    void loadGraphMat(string, int, int);
};

void Graph::loadGraphList(string input, int n) {
    nodes = n;
    adjList = new vector<int>[nodes];
    
    stringstream ss(input);
    string edge;
    while (getline(ss, edge, ')')) {
        if (edge.length() >= 3) {
            size_t start = edge.find('(');
            if (start != string::npos) {
                size_t comma = edge.find(',');
                if (comma != string::npos) {
                    string u_str = edge.substr(start + 1, comma - start - 1);
                    string v_str = edge.substr(comma + 1);
                    
                    u_str.erase(remove(u_str.begin(), u_str.end(), ' '), u_str.end());
                    v_str.erase(remove(v_str.begin(), v_str.end(), ' '), v_str.end());
                    
                    if (!u_str.empty() && !v_str.empty()) {
                        int u = stoi(u_str);
                        int v = stoi(v_str);
                        addEdgeAdjList(u, v);
                    }
                }
            }
        }
    }
    sortAdjList();
}

void Graph::loadGraphMat(string input, int n, int m) {
    nodes = n;
    adjMatrix = new int[nodes * nodes];
    for (int i = 0; i < nodes * nodes; i++)
        adjMatrix[i] = 0;
    
    stringstream ss(input);
    string edge;
    while (getline(ss, edge, ')')) {
        if (edge.length() >= 3) {
            size_t start = edge.find('(');
            if (start != string::npos) {
                size_t comma = edge.find(',');
                if (comma != string::npos) {
                    string u_str = edge.substr(start + 1, comma - start - 1);
                    string v_str = edge.substr(comma + 1);
                    
                    u_str.erase(remove(u_str.begin(), u_str.end(), ' '), u_str.end());
                    v_str.erase(remove(v_str.begin(), v_str.end(), ' '), v_str.end());
                    
                    if (!u_str.empty() && !v_str.empty()) {
                        int u = stoi(u_str);
                        int v = stoi(v_str);
                        addEdgeAdjMatrix(u, v);
                    }
                }
            }
        }
    }
}

Graph::Graph() {
    edgesList = edgesMat = 0;
    nodes = 0;
    adjList = nullptr;
    adjMatrix = nullptr;
}

Graph::Graph(int n) {
    nodes = n;
    adjList = new vector<int>[nodes];
    adjMatrix = new int[nodes * nodes];
    for (int i = 0; i < nodes * nodes; i++)
        adjMatrix[i] = 0;
    edgesList = edgesMat = 0;
}

void Graph::addEdgeAdjList(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
    edgesList++;
}

void Graph::addEdgeAdjMatrix(int u, int v) {
    adjMatrix[u * nodes + v] = 1;
    adjMatrix[v * nodes + u] = 1;
    edgesMat++;
}

string Graph::printAdjList() {
    stringstream aux;
    for (int i = 0; i < nodes; i++) {
        aux << "vertex " << i << " :";
        for (size_t j = 0; j < adjList[i].size(); j++) {
            aux << " " << adjList[i][j];
        }
        aux << " ";
    }
    return aux.str();
}

void Graph::sortAdjList() {
    for (int i = 0; i < nodes; i++)
        sort(adjList[i].begin(), adjList[i].end());
}

string Graph::printAdjMat() {
    stringstream aux;
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            aux << adjMatrix[i * nodes + j] << " ";
        }
    }
    return aux.str();
}

string Graph::DFS(int start, int goal) {
    vector<bool> visited(nodes, false);
    vector<int> parent(nodes, -1);
    stack<pair<int, int>> st; 
    list<int> visited_order;

    st.push({start, start});

    while (!st.empty()) {
        int current = st.top().first;
        int parent_current = st.top().second;
        st.pop();

        if (!visited[current]) {
            visited[current] = true;
            parent[current] = parent_current;
            visited_order.push_back(current);

            if (current == goal) {
                break;
            }

            for (int i = static_cast<int>(adjList[current].size()) - 1; i >= 0; i--) {
                int neighbor = adjList[current][i];
                if (!visited[neighbor]) {
                    st.push({neighbor, current});
                }
            }
        }
    }

    stringstream aux;
    aux << "visited: ";
    for (int node : visited_order) {
        aux << node << " ";
    }
    
    aux << "path:";
    if (parent[goal] == -1) {
        aux << " not found";
    } else {
        stack<int> path;
        int node = goal;
        while (node != start) {
            path.push(node);
            node = parent[node];
        }
        path.push(start);
        
        while (!path.empty()) {
            aux << " " << path.top();
            path.pop();
        }
    }
    
    return aux.str();
}

string Graph::BFS(int start, int goal) {
    vector<bool> visited(nodes, false);
    vector<int> parent(nodes, -1);
    queue<pair<int, int>> q; 
    list<int> visited_order;

    q.push({start, start});
    visited[start] = true;
    parent[start] = start;

    while (!q.empty()) {
        int current = q.front().first;
        int parent_current = q.front().second;
        q.pop();
        
        visited_order.push_back(current);
        parent[current] = parent_current;

        if (current == goal) {
            break;
        }

        for (size_t i = 0; i < adjList[current].size(); i++) {
            int neighbor = adjList[current][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push({neighbor, current});
            }
        }
    }

    stringstream aux;
    aux << "visited: ";
    for (int node : visited_order) {
        aux << node << " ";
    }
    
    aux << "path:";
    if (parent[goal] == -1) {
        aux << " not found";
    } else {
        stack<int> path;
        int node = goal;
        while (node != start) {
            path.push(node);
            node = parent[node];
        }
        path.push(start);
        
        while (!path.empty()) {
            aux << " " << path.top();
            path.pop();
        }
    }
    
    return aux.str();
}

#endif