#include "CourseSchedule.h"


int main(){

    int num;
    int numPrereq;
    vector<vector<int>> prereq;

    cout << "Enter number of courses to take: ";
    cin >> num;
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
        prereq.push_back({toTake, required});
    }
    
    CourseSchedule s(num, prereq);
    vector<int> answer = s.findSchedule();

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