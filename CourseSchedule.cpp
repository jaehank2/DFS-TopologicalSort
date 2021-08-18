#include "CourseSchedule.h"


CourseSchedule::CourseSchedule(int num, vector<vector<int>>& prereq){
    numCourses = num;
    prerequisites = prereq;
}

/**
 * @brief returns an ordering of courses to take to finish them all
 * 
 * @param numCourses - number of courses to take
 * @param prerequisites - [toTake, required] where one must take "required" to take "toTake"
 * 
 * @return vector of courses in order or an empty vector if not possible
 * 
 */
vector<int> CourseSchedule::findSchedule(){
    vector<int> answer;
        
    if (prerequisites.empty()){
        for (int i=0; i<numCourses; i++){
            answer.push_back(i);
        }
        return answer;
    }
        
    unordered_set<int> vis;
    unordered_set<int> root;
        
        
    Graph g(numCourses);
    for (int i=0; i<prerequisites.size(); i++){  
        g.addEdge(prerequisites[i][0], prerequisites[i][1]);
    }
        
    // topo requires DAG and DAG must have at least one source and one sink
    int time = 0;
    vector<int> pre(numCourses, 0);
    vector<int> post(numCourses, 0);
    bool backwardEdge = false;

    auto cmp = [](pair<int, int> a, pair<int, int> b){
        return a.second > b.second;
    };
        
    /// @brief pq - to return topological sort in asc order
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
    for (int i=0; i<numCourses; i++){
        if (!vis.count(i)){
            DFS(g, i, time, pre, post, vis, backwardEdge);
            if (backwardEdge == true){
                return answer;
            }
        }
    }
        
    for (int i=0; i<post.size(); i++){
        pq.push({i, post[i]});
    }
    while (answer.size() < numCourses){
        pair<int, int> tp = pq.top();
        pq.pop();
        answer.push_back(tp.first);
    }
        
    return answer;
}


/**
 * @brief performs DFS while keeping track of 'time' to output topological ordering
 * 
 * @param g - graph on which DFS is performed
 * @param src - source node/current node in graph
 * @param time - counter to account for when a node is first and last visited
 * @param pre - vector keeping track of when nodes are first visited
 * @param post - vector keeping track of when nodes are last visited
 * @param vis - set of visited nodes
 * @param flag - boolean to signify existence of backward edge
 * 
 */
void CourseSchedule::DFS(Graph& g, int src, int& time, vector<int>& pre, vector<int>& post, unordered_set<int>& vis, bool& flag){
    vis.insert(src);
    pre[src] = time++;
    for (int i=0; i<g.adj[src].size(); i++){
        int temp = g.adj[src][i];
        if (!vis.count(g.adj[src][i])){
            DFS(g, g.adj[src][i], time, pre, post, vis, flag);
        }
        else{
            // backward edge = cycle
            if (post[g.adj[src][i]] == 0){  // meaning g.adj[src][i] has been visited again while it is still being process (hence post==0)
                cout << endl;
                cout << "****************" << endl;
                cout << "ERROR: resolve dependency issue for course " << g.adj[src][i] << endl;
                cout << "****************" << endl;
                flag = true;
                return;
            }
        }
    }
    post[src] = time++;
}
