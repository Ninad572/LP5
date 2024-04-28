#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>
#include<ctime>
using namespace std;

// Function to perform DFS traversal
void parallelDFS(int startNode, const vector<vector<int>>& graph, vector<bool>& visited) {
    stack<int> stack;
    stack.push(startNode);
    while (!stack.empty()) {
        int currentNode = stack.top();
        
        stack.pop();
        if (!visited[currentNode]) {
            visited[currentNode] = true;
            cout << "Visited node: " << currentNode << endl;
            // Parallelize the loop for traversing neighbors
            #pragma omp parallel for
            for (int i = 0; i < graph[currentNode].size(); ++i) {
                int neighbor = graph[currentNode][i];
                if (!visited[neighbor]) {
                    stack.push(neighbor);
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

    // Perform parallel DFS traversal from each unvisited node
clock_t start=clock();
    for (int i = 0; i < numNodes; ++i) {
        if (!visited[i]) {
            parallelDFS(i, graph, visited);
        }
    }
    clock_t end=clock();
    cout<<double(end-start)/CLOCKS_PER_SEC;
    return 0;
}
