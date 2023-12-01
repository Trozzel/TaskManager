//
// Created by George Ford on 1/28/22.
//
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <system_error>
#include <type_traits>

#include "GtdBase.hpp"
#include "GtdHelper.hpp"
#include "Task.hpp"

using namespace std;

namespace gtd {

// STATIC FUNCTIONS
constexpr TaskType 
Task::strToTaskType(std::string_view taskTypeStr) noexcept {
	TaskType taskType;
	if (taskTypeStr == "Parallel") {
		taskType = TaskType::Parallel;
	}
	else if (taskTypeStr == "Sequential") {
		taskType = TaskType::Sequential;
	}
	else {
		fmt::print(stderr, "Incorrect Task Type String: '{}'\n", taskTypeStr);
		taskType = TaskType::Parallel;
	}
	return taskType;
}

// SETTERS
/*****************************************************************************/
void
Task::setTaskType(const std::string &taskType) {
	// gtd::Project should not access this method
	static_assert(std::is_same_v<decltype(*this), Task&>);
    _taskType = strToTaskType(taskType);
}

std::ostream& 
operator<<(std::ostream& out, const Task& task) {
    // SEND BASE TO STREAM
    const auto* pBase = static_cast<const GtdBase*>(&task);
    out << *pBase;

    // SEND REMAINED TO STREAM
    out << task.notes() << " " << timePointToStr(task.deferred()) << " "
        << timePointToStr(task.due()) << " "
        << taskTypeString(task.taskType()) << " "
        << ios::boolalpha << task.isRepeating(); 

    return out;
}

} // namespace gtd
