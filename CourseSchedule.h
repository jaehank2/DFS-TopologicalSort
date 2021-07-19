#pragma once
#include "Graph.h"


class CourseSchedule {
public:
    int numCourses = 0;
    vector<vector<int>> prerequisites;

    CourseSchedule(int num, vector<vector<int>>& prereq);
    /**
    * @brief returns an ordering of courses to take to finish them all
    * 
    * @param numCourses - number of courses to take
    * @param prerequisites - [toTake, required] where one must take "required" to take "toTake"
    * 
    * @return vector of courses in order or an empty vector if not possible
    */
    vector<int> findSchedule();


    /**
     * @brief DFS for topological sort
     * 
     */
    // usually a->b means a only then b (b depends on a) and topo with post time in desc order
    // but for this we had in reverse (a depends on b) so topo in asc order
    void DFS(Graph& g, int src, int& time, vector<int>& pre, vector<int>& post, unordered_set<int>& vis, bool& flag);
    
};