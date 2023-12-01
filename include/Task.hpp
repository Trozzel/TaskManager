//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_TASK_HPP
#define GTD_TASK_HPP

#include <iostream>
#include <string>
#include <filesystem>
#include <string_view>
#include <type_traits>

#include "CompletableBase.hpp"
#include "GtdHelper.hpp"

namespace gtd {

/// \brief gtd::Task mirrors the table, tasks, as an in-memoy storage of a
/// given task
/// \param _contextId - uniqueId of the context to which task is assigned
/// \param _projectId - uniqueId of the project to which the task belongs
/// \param _notes - notes
/// \param _deferred - deferred start date 
/// \param _due - due date 
/// \param _taskType of enum class TaskType. Either Sequential or Parallel 
/// \param _isRepeating - if this is a recurring task
/// \param _flagged - is flagged or not
/// \param _repeatSchedule - crontab format repeat schedule
class Task final : public CompletableBase {
private:
	// hide from Project since Project has a ProjectType
    TaskType            _taskType {TaskType::Parallel};
    LL_t                _projectId {-1};

public:
    // STATIC FUNCTIONS
    static constexpr
    TaskType strToTaskType(std::string_view taskTypeStr) noexcept; 

    // CTORS
    Task(std::string_view name = "") :
            CompletableBase(name) {
    }

    ~Task() final = default;

    [[nodiscard]] [[maybe_unused]]
	constexpr LL_t 
    projectId() const noexcept {
        return _projectId;
    }

    [[nodiscard]] [[maybe_unused]]
	constexpr TaskType 
    taskType() const noexcept {
        return _taskType;
    }

    // SETTERS
    /*************************************************************************/
    [[maybe_unused]]
	constexpr void 
    setProjectId(LL_t projectId) noexcept {
        _projectId = projectId;
    }

	void 
    setProjectIdFromStr(const std::string& projectIdStr) {
        _projectId = (projectIdStr.empty()) ? -1 : std::stoll(projectIdStr);
    }

	[[maybe_unused]]
	constexpr void 
    setTaskType(TaskType taskType) noexcept {
		_taskType = taskType;
	}

	[[maybe_unused]]
	void 
    setTaskType(const std::string &taskType);

};

} // namespace gtd

std::ostream&
operator<<(std::ostream &out, const gtd::Task &task);

#endif //GTD_TASK_HPP
