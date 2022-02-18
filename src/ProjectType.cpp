//
// Created by George Ford on 2/5/22.
//

#include "ProjectType.hpp"

namespace gtd {

std::string projectTypeString(ProjectType projectType) {
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
} // namespace gtd