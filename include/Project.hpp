//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_PROJECT_HPP
#define GTD_PROJECT_HPP

#include <string>
#include <list>

#include "CTime.hpp"
#include "ProjectType.hpp"
#include "Status.hpp"
#include "Context.hpp"

namespace gtd {

class Project {
private:
    std::string _projectName{};
    std::string _note{};
    Status      _status           { Status::Active };
    ProjectType _projectType      { ProjectType::Parallel };
    bool        _completeWithLast { false };

    std::list<const Context*> _contexts;

    dt::CTime _created{};
    dt::CTime _modified{};
    dt::CTime _deferred{};
    dt::CTime _due{};
    dt::CTime _completed{};
    dt::CTime _dropped;

public:

};

} // namespace gtd


#endif //GTD_PROJECT_HPP
