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
            root.insert(prerequisites[i][0]);
            g.addEdge(prerequisites[i][0], prerequisites[i][1]);
        }
        
        bool srcEmpty = true;
        
        for (int i=0; i<prerequisites.size(); i++){
            if (root.count(prerequisites[i][1])){
                root.erase(prerequisites[i][1]);    // get root nodes
            }
            if (g.adj[prerequisites[i][1]].empty()){    // leaf nodes
                srcEmpty = false;
            }
        }
        
        if (srcEmpty) return answer;
        int time = 0;
        vector<int> post(numCourses, 0);

        auto cmp = [](pair<int, int> a, pair<int, int> b){
            return a.second > b.second;
        };
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
        for (auto it=root.begin(); it != root.end(); it++){
            DFS(g, *it, time, post, vis);
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
    void DFS(Graph& g, int src, int& time, vector<int>& post, unordered_set<int>& vis){
        vis.insert(src);
        time++;
        for (int i=0; i<g.adj[src].size(); i++){
            if (!vis.count(g.adj[src][i])){
                DFS(g, g.adj[src][i], time, post, vis);
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
    cout << "The ordering of your schedule should be: " << endl;
    for (int i=0; i<answer.size(); i++){
        cout << answer[i] << " ";
    }
    cout << endl;
    cout << "**Note that the answer may not be unique" << endl;

    return 0;
}