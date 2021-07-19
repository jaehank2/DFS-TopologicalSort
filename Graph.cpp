#include "Graph.h"


/**
 * @brief Graph class with adjacency list
 * 
 */
Graph::Graph(int numCourses){
    nodes = numCourses;
    adj = new vector<int> [numCourses];
}

void Graph::addEdge(int src, int dest){
    adj[src].push_back(dest);
}
