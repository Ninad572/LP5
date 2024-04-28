#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

// Function to perform BFS traversal
void parallelBFS(int startNode, const vector<vector<int>>& graph, vector<bool>& visited) {
    queue<int> queue;
    queue.push(startNode);
    while (!queue.empty()) {
        int currentNode = queue.front();
        queue.pop();
        
        if (!visited[currentNode]) {
            visited[currentNode] = true;
            cout << "Visited node: " << currentNode << endl;
            // Parallelize the loop for traversing neighbors
            #pragma omp parallel for
            for (int i = 0; i < graph[currentNode].size(); ++i) {
                int neighbor = graph[currentNode][i];
                if (!visited[neighbor]) {
                    queue.push(neighbor);
                }
            }
        }
    }
}

int main() {
    // Example graph represented as an adjacency list
    vector<vector<int>> graph = {
        {1, 2},     // Node 0
        {0, 3, 4},  // Node 1
        {0, 5},     // Node 2
        {1},        // Node 3
        {1},        // Node 4
        {2}         // Node 5
    };

    int numNodes = graph.size();
    vector<bool> visited(numNodes, false);

    // Perform parallel BFS traversal from each unvisited node
    
    for (int i = 0; i < numNodes; ++i) {
        if (!visited[i]) {
            parallelBFS(i, graph, visited);
        }
    }

    return 0;
}
