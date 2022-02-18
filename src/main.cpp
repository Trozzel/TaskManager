#include <iostream>

#include "Project.hpp"

using namespace std;

int main() {
    gtd::Project project;
    project.setProjectName("Stuff to do");

    cout << project.projectName() << endl;
//    project.set
    return 0;
}
