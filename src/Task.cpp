//
// Created by George Ford on 1/28/22.
//
#include "Task.hpp"

using namespace std;

namespace gtd {
// CTORS
Task::Task( TaskContainer& gtdItems, std::string_view name ) :
    Completable(gtdItems, name),
    _gtdItems(gtdItems)
{
    _gtdItems.push_back(this);
}

// SETTERS
/*****************************************************************************/
void
Task::setProjectId( unique_id_t id, bool update ) {
    _projectId = id;
    pushToUpdateStack("projectId", projectId(), update);
}

void
Task::setTaskType( const TaskType type, bool update ) {
    _taskType = type;
    pushToUpdateStack("taskType", taskTypeString(_taskType), update);
}

void
Task::setTaskType( std::string_view type, bool update ) {
    _taskType = strToTaskType(type);
    pushToUpdateStack("taskType", taskTypeString(_taskType), update);
}

std::ostream&
operator<<( std::ostream& out, const Task& task ) {
    // SEND BASE TO STREAM
    const auto* pBase = static_cast<const GtdBase*>(&task);
    out << *pBase;

    // SEND REMAINED TO STREAM
    out << *task.notes() << " "
            << *task.deferredStr() << " "
            << *task.dueStr() << " "
            << taskTypeString(task.taskType()) << " "
            << ios::boolalpha << task.isRepeating();

    return out;
}
} // namespace gtd
