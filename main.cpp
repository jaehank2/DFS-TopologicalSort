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
    
    Graph(int numCourses){  // custom constructor
        nodes = numCourses;
        adj = new vector<int> [numCourses];
    }
    
    void addEdge(int src, int dest){
        adj[src].push_back(dest);
    }
    
};

/**
 * @brief returns an ordering of courses to take to finish them all
 * 
 * @param numCourses - number of courses to take
 * @param prerequisites - [toTake, required] where one must take "required" to take "toTake"
 * 
 * @return vector of courses in order or an empty vector if not possible
 * 
 */
class CourseSchedule {
public:
    vector<int> findSchedule(int numCourses, vector<vector<int>>& prerequisites) {
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
     * @brief DFS for topological sort
     * 
     */
    // usually a->b means a only then b (b depends on a) and topo with post time in desc order
    // but for this we had in reverse (a depends on b) so topo in asc order
    void DFS(Graph& g, int src, int& time, vector<int>& pre, vector<int>& post, unordered_set<int>& vis, bool& flag){
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
};

int main(){

    int numCourses;
    int numPrereq;
    vector<vector<int>> prerequisites;

    cout << "Enter number of courses to take: ";
    cin >> numCourses;
    cout << "Enter total number of prerequisites related to your courses: ";
    cin >> numPrereq;
    cout << endl;
    for (int i=0; i<numPrereq; i++){
        int toTake;
        int required;
        cout << "Enter your " << i << "th course to take that has a prereq: ";
        cin >> toTake;
        cout << "Enter your prereq course for your " << i << "th course: ";
        cin >> required;
        prerequisites.push_back({toTake, required});
    }
    
    CourseSchedule s;
    vector<int> answer = s.findSchedule(numCourses, prerequisites);

    cout << endl;
    if (answer.size() == 0){
        cout << "no valid ordering" << endl;
    }
    else {
        cout << "The ordering of your schedule should be: " << endl;
        for (int i=0; i<answer.size(); i++){
            cout << answer[i] << " ";
        }
        cout << endl;
        cout << "**Note that the answer may not be unique" << endl;
    }
    

    return 0;
}