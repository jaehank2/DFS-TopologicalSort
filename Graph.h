#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <stack>
#include <unordered_map>

using namespace std;

/**
 * @brief Graph class with adjacency list
 * 
 */
class Graph {
public:
    int nodes;
    vector<int>* adj;
    
    Graph(int numCourses);
    
    void addEdge(int src, int dest);
    
};