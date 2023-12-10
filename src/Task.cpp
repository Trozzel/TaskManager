//
// Created by George Ford on 1/28/22.
//
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <system_error>
#include <type_traits>

#include "Task.hpp"

using namespace std;

namespace gtd {

// CTORS
Task::Task(USMgr& updateStackMgr, std::string_view name) :
	CompletableBase(updateStackMgr, name) {}

// SETTERS
/*****************************************************************************/
void
Task::setProjectId(unique_id_t projectId, bool update) {
	_projectId = projectId;
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "projectId");
	}
}

void
Task::setTaskType(TaskType taskType, bool update) {
	_taskType = taskType;
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "taskType");
	}
}

void
Task::setTaskType(std::string_view taskType, bool update) {
    _taskType = strToTaskType(taskType);
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "taskType");
	}
}

std::ostream& 
operator<<(std::ostream& out, const Task& task) {
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
