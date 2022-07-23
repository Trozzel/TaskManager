//
// Created by George Ford on 2/5/22.
//

#include "ProjectType.hpp"

using namespace std;

namespace gtd {

string projectTypeString(ProjectType projectType) {
    std::string projTypeStr{};
    switch (projectType) {
        case ProjectType::Parallel:
            projTypeStr = "Parallel";
            break;
        case ProjectType::Sequential:
            projTypeStr = "Sequential";
            break;
        case ProjectType::SingleActions:
            projTypeStr = "SingleActions";
            break;
    }
    return projTypeStr;
}

string projectTypeString(ProjectType projectType) {
    string ptStr;
    switch (projectType) {
    case ProjectType::Parallel:
        ptStr = "Parallel";
        break;
    case ProjectType::Sequential:
        ptStr = "Sequential";
        break;
    case ProjectType::SingleActions:
        ptStr = "Single Actions";
        break;
    }
    return ptStr;
}
} // namespace gtd