<h1 align="center"> DFS-TopologicalSort </h1>

## Summary ##
CourseScheduler that will give you a valid ordering of courses to take by taking in the inputs for
  1. number of courses one plans on taking
  2. all the prerequisites in the form of [toTake, required] where in order to take "toTake", one must take "required"

## Input Explanation ##
The total number of prerequisites should count each [toTake, required] as 1

:warning: ***The returned ordering may not be a unique solution*** :warning:

## Executables ##
* Clone the repository
* Compile it (eg. `g++ main.cpp -o {executable name}`)
* Run (eg. `./{executable name}`)
* Enter all inputs printed on screen

## Algorithms/Data Structure ##
* Graph with adjacency list
* DFS with topological sort
* Cycle Detection through backward edge
* Priority queue
* Lambda expression

## Sample Output
* Case with cycle (no return value)
  <img src="misc/case1.PNG" width="400" height="400">
* Case with no cycle
  <img src="misc/case2.PNG" width="400" height="400">
