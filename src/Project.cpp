#include "Task.hpp"
#include "Project.hpp"
#include "GtdHelper.hpp"
#include "GtdContainer.hpp"

using namespace std;

namespace gtd {
// CTORS
/*****************************************************************************/
Project::Project( const sp_Container& projects, const std::string_view name ) :
    Completable(name),
    _projects(projects) {}

// ASSIGNMENT OPERATORS
/*****************************************************************************/
Project&
Project::operator=( const Project& other ) {
    if ( this != &other ) {
        Completable::operator=(other);
        _projects         = other._projects;
        _projectType      = other._projectType;
        _folderId         = other._folderId;
        _taskIds          = other._taskIds;
        _completeWithLast = other._completeWithLast;
        _reviewSchedule   = other._reviewSchedule;
    }
    return *this;
}

// COMPARISON OPERATORS
/*****************************************************************************/
bool
Project::operator==( const Project& other ) const {
    return Completable::operator==(other) &&
            //_projects == other._projects &&
            _projectType == other._projectType &&
            _folderId == other._folderId &&
            _taskIds == other._taskIds && // Is this necessary?
            _completeWithLast == other._completeWithLast &&
            _reviewSchedule == other._reviewSchedule;
}

bool
Project::operator!=( const Project& other ) const {
    return !operator==(other);
}

// OVERRIDE SETTERS
/*****************************************************************************/
void
Project::setName( const std::string_view name, const bool update ) {
    Completable::setName(name, update);
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "name", this->name());
        }
    }
}

void
Project::setStatus( const std::string_view status, const bool update ) {
    Completable::setStatus(status, update);
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "status", statusStr());
        }
    }
}

void
Project::setStatus( const Status status, const bool update ) {
    Completable::setStatus(status, update);
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "status", statusStr());
        }
    }
}

void
Project::setParentId( const unique_id_t id, const bool update ) {
    Completable::setParentId(id, update);
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "parent", *parentId());
        }
    }
}

void
Project::setNotes( const std::string_view notes, const bool update ) {
    Completable::setNotes(notes, update);
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "notes", *this->notes());
        }
    }
}

void
Project::setContextId( const unique_id_t id, const bool update ) {
    Completable::setContextId(id, update);
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "context", *contextId());
        }
    }
}

void
Project::setDeferred( const time_point_t deferred, const bool update ) {
    Completable::setDeferred(deferred, update);
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "deferred", *deferredStr());
        }
    }
}

void
Project::setDeferred( const std::string_view deferred, const bool update ) {
    Completable::setDeferred(deferred, update);
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "deferred", *deferredStr());
        }
    }
}

void
Project::setDue( const time_point_t tp, const bool update ) {
    Completable::setDue(tp, update);
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "due", *dueStr());
        }
    }
}

void
Project::setDue( const std::string_view due_str, const bool update ) {
    Completable::setDue(due_str, update);
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "due", *dueStr());
        }
    }
}

void
Project::setTaskType( const std::string& taskType, const bool update ) {
    Completable::setTaskType(taskType, update);
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "taskType", taskType);
        }
    }
}

void
Project::setIsRepeating( const int isRepeating, const bool update ) {
    Completable::setIsRepeating(isRepeating, update);
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "isRepeating", this->isRepeating());
        }
    }
}

void
Project::setFlagged( const int flagged, const bool update ) {
    Completable::setFlagged(flagged, update);
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "flagged", this->flagged());
        }
    }
}

void
Project::setRepeatFrom( const RepeatFrom repeatFrom, const bool update ) {
    Completable::setRepeatFrom(repeatFrom, update);
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "repeatFrom", repeatFromStr());
        }
    }
}

void
Project::setRepeatFrom( const std::string_view rptFromStr, const bool update ) {
    Completable::setRepeatFrom(rptFromStr, update);
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "repeatFrom", repeatFromStr());
        }
    }
}

void
Project::setRepeatSchedule( const std::string_view schedule, const bool update ) {
    Completable::setRepeatSchedule(schedule, update);
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "repeatSchedule", repeatSchedule());
        }
    }
}

// PROJECT SETTERS
/*****************************************************************************/
void
Project::setTaskIds( const std::initializer_list<unique_id_t>& taskIds ) {
    _taskIds = taskIds;
}

void
Project::setTaskIds( const std::vector<unique_id_t>& taskIds ) {
    _taskIds = taskIds;
}

void
Project::appendTaskIds( const std::vector<unique_id_t>& taskIds ) {
    _taskIds.insert(_taskIds.end(), taskIds.begin(), taskIds.end());
}

void
Project::appendTaskIds( const std::initializer_list<unique_id_t>& taskIds ) {
    for ( unsigned long long taskId : taskIds ) {
        _taskIds.push_back(taskId);
    }
}

void
Project::appendTaskId( const unique_id_t taskId ) {
    _taskIds.push_back(taskId);
}

void
Project::setProjectType( const ProjectType projectType, const bool update ) {
    _projectType = projectType;
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        us.push(*uniqueId(), "projectType", projectTypeStr(_projectType));
    }
}

void
Project::setProjectType( const std::string_view projectType, const bool update ) {
    _projectType = strToProjectType(projectType);
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        us.push(*uniqueId(), "projectType", projectTypeStr(_projectType));
    }
}

void
Project::setFolderId( const unique_id_t id, const bool update ) {
    _folderId = id;
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        us.push(*uniqueId(), "folder", *folderId());
    }
}

void
Project::setCompleteWithLast( const bool completeWithLast, const bool update ) {
    _completeWithLast = completeWithLast;
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        us.push(*uniqueId(), "completeWithLast", _completeWithLast);
    }
}

void
Project::setReviewSchedule( const std::string_view reviewSchedule, const bool update ) {
    _reviewSchedule = reviewSchedule;
    if ( update ) {
        auto& us = _projects.lock()->updateStack();
        us.push(*uniqueId(), "reviewSchedule", this->reviewSchedule());
    }
}

//std::ostream&
//operator<<( std::ostream& out, const Project& project ) {
//    // SEND BASE TO STREAM
//    const auto* pBase = static_cast<const GtdBase*>(&project);
//    out << *pBase;
//
//    // SEND REMAINED TO STREAM
//    out << *project.notes() << " "
//            << *project.deferredStr()
//            << *project.dueStr() << " "
//            << projectTypeStr(project.projectType()) << " "
//            << ios::boolalpha << project.isRepeating() << " "
//            << project.repeatFromStr() << " ";
//
//    return out;
//}
} // namespace gtd
