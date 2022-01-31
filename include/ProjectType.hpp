//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_PROJECTTYPE_HPP
#define GTD_PROJECTTYPE_HPP

#include <string>

/**
 * @brief enum class describing various types of Projects
 */
enum class ProjectType {
    Parallel, Sequential, SingleActions
};

std::string projectTypeString(ProjectType projectType) {
    std::string projTypeStr {};
    switch (projectType) {
        case ProjectType::Parallel:
            projTypeStr = "Parallel";
            break;
        case ProjectType::Sequential:
            projTypeStr = "Sequential":
                    break;
        case ProjectType::SingleActions:
            projTypeStr = "SingleActions";
            break;
    }
    return projTypeStr;
}

#endif //GTD_PROJECTTYPE_HPP
