//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_TASK_HPP
#define GTD_TASK_HPP

#include <iostream>
#include <string>
#include <string_view>

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
    TaskType								_taskType { TaskType::Parallel };
	std::optional<unique_id_t>  			_projectId { std::nullopt };

public:
    // STATIC FUNCTIONS
    static constexpr
    TaskType strToTaskType(std::string_view taskTypeStr) noexcept {
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

	constexpr static
	std::string_view
	tableName() noexcept {
		return "tasks";
	};

    // CTORS
    explicit Task(USMgr&, std::string_view name = "");

	// DTOR
    ~Task() final = default;

	// GETTERS
	/*************************************************************************/
    [[nodiscard]] [[maybe_unused]]
	constexpr std::optional<unique_id_t>
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
	void
    setProjectId(unique_id_t projectId, bool update = true);

	void
    setTaskType(TaskType taskType, bool update = true);

	void
    setTaskType(std::string_view taskType, bool update = true);

};

} // namespace gtd

std::ostream&
operator<<(std::ostream &out, const gtd::Task &task);

#endif //GTD_TASK_HPP
