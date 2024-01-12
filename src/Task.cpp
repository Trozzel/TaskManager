//
// Created by George Ford on 1/28/22.
//
#include "Task.hpp"
#include "GtdContainer.hpp"
#include "UpdateStack.hpp"


namespace gtd {
// CTORS
/*****************************************************************************/
Task::Task( pContainer tasks, const std::string_view name ) :
    Completable(name),
    _tasks(std::move(tasks)) {
    // _tasks->push_back(*this);
    std::cout << "Task COPY CTOR\n";
}

Task::Task( GtdContainer<Task>* tasks, const std::string_view name ) :
Completable(name),
_tasks(tasks)
{ }

Task::Task( Task&& other ) noexcept :
    Completable(std::move(other)),
    _tasks(std::move(other._tasks)),
    _taskType(other._taskType),
    _o_projectId(other._o_projectId) {
    std::cout << "Task MOVE CTOR\n";
}

/*****************************************************************************/
Task&
Task::operator=( const Task& other ) {
    if ( &other != this ) {
        Completable::operator=(other);
        _tasks       = other._tasks;
        _taskType    = other._taskType;
        _o_projectId = other._o_projectId;
    }
    return *this;
}

Task&
Task::operator=( Task&& other ) noexcept {
    if ( &other != this ) {
        Completable::operator=(other);
        _tasks       = std::move(other._tasks);
        _taskType    = other._taskType;
        _o_projectId = other._o_projectId;
    }
    return *this;
}

// COMPARISON OPERATORS
/*****************************************************************************/
bool
Task::operator==( const Task& other ) const {
    return Completable::operator==(other) &&
            _taskType == other._taskType &&
            _o_projectId == other._o_projectId;
}

bool
Task::operator!=( const Task& other ) const {
    return !operator==(other);
}

// SETTERS
/*****************************************************************************/
// 1. NON-VIRTUAL Task METHODS
/*****************************************************************************/
void
Task::setProjectId( const unique_id_t projectId, const bool update ) {
    _o_projectId = projectId;
    if ( update ) {
        if ( _o_uniqueId ) {
            auto& us = _tasks->updateStack();
            us.push(*uniqueId(), "projectId", *this->projectId());
        }
    }
}

void
Task::setTaskType( const TaskType taskType, const bool update ) {
    _taskType = taskType;
    if ( update ) {
        if ( (_o_uniqueId) ) {
            auto& us = _tasks->updateStack();
            us.push(*uniqueId(), "taskType", taskTypeString(taskType));
        }
    }
}

void
Task::setTaskType( const std::string_view taskType, const bool update ) {
    _taskType = strToTaskType(taskType);
    if ( (_o_uniqueId) ) {
        auto& us = _tasks->updateStack();
        us.push(*uniqueId(), "taskType", taskTypeString(_taskType));
    }
}

void
Task::setStatus( const std::string_view status, const bool update ) {
    Completable::setStatus(status, update);
    if ( update ) {
        auto& us = _tasks->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "status", *deferredStr());
        }
    }
}

void
Task::setStatus( const Status status, bool update ) {
    Completable::setStatus(status, update);
    if ( update ) {
        auto& us = _tasks->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "status", *deferredStr());
        }
    }
}

void
Task::setParentId( const unique_id_t id, const bool update ) {
    Completable::setParentId(id, update);
    if ( update ) {
        auto& us = _tasks->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "parent", *deferredStr());
        }
    }
}

void
Task::setNotes( const std::string_view notes, const bool update ) {
    Completable::setNotes(notes, update);
    if ( update ) {
        auto& us = _tasks->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "notes", *deferredStr());
        }
    }
}

void
Task::setContextId( const unique_id_t contextId, const bool update ) {
    Completable::setContextId(contextId, update);
    if ( update ) {
        auto& us = _tasks->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "context", *deferredStr());
        }
    }
}

void
Task::setDeferred( const time_point_t deferred, const bool update ) {
    Completable::setDeferred(deferred, update);
    if ( update ) {
        auto& us = _tasks->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "deferred", *deferredStr());
        }
    }
}

void
Task::setDeferred( const std::string_view deferred, const bool update ) {
    Completable::setDeferred(deferred, update);
    if ( update ) {
        auto& us = _tasks->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "deferred", *deferredStr());
        }
    }
}

void
Task::setDue( const time_point_t tp, const bool update ) {
    Completable::setDue(tp, update);
    if ( update ) {
        auto& us = _tasks->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "due", *deferredStr());
        }
    }
}

void
Task::setDue( const std::string_view due_str, const bool update ) {
    Completable::setDue(due_str, update);
    if ( update ) {
        auto& us = _tasks->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "due", *deferredStr());
        }
    }
}

void
Task::setIsRepeating( const int isRepeating, const bool update ) {
    Completable::setIsRepeating(isRepeating, update);
    if ( update ) {
        auto& us = _tasks->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "isRepeating", *deferredStr());
        }
    }
}

void
Task::setFlagged( const int flagged, const bool update ) {
    Completable::setFlagged(flagged, update);
    if ( update ) {
        auto& us = _tasks->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "flagged", *deferredStr());
        }
    }
}

void
Task::setRepeatFrom( const RepeatFrom repeatFrom, const bool update ) {
    Completable::setRepeatFrom(repeatFrom, update);
    if ( update ) {
        auto& us = _tasks->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "repeatFrom", *deferredStr());
        }
    }
}

void
Task::setRepeatFrom( const std::string_view rptFromStr, const bool update ) {
    Completable::setRepeatFrom(rptFromStr, update);
    if ( update ) {
        auto& us = _tasks->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "repeatFrom", *deferredStr());
        }
    }
}

void
Task::setRepeatSchedule( const std::string_view schedule, const bool update ) {
    Completable::setRepeatSchedule(schedule, update);
    if ( update ) {
        auto& us = _tasks->updateStack();
        if ( this->uniqueId() ) {
            us.push(*this->uniqueId(), "repeatSchedule", *deferredStr());
        }
    }
}


//sdefaulttd::ostream&
//operator<<( std::ostream& out, const Task& task ) {
//    // SEND BASE TO STREAM
//	const auto pUpdateStack = _updateStackMgr.getUpdateStack();
//    out << *pBase;
//
//    // SEND REMAINED TO STREAM
//    out << *task.notes() << " "
//            << *task.deferredStr() << " "
//            << *task.dueStr() << " "
//            << taskTypeString(task.taskType()) << " "
//            << ios::boolalpha << task.isRepeating();
//
//    return out;
//}
} // namespace gtd
