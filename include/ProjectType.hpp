//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_PROJECTTYPE_HPP
#define GTD_PROJECTTYPE_HPP

#include <string>

namespace gtd {

/**
 * @brief enum class describing various types of Projects
 */
enum class ProjectType {
    Parallel, Sequential, SingleActions
};

std::string projectTypeString(ProjectType projectType);
}

#endif //GTD_PROJECTTYPE_HPP
