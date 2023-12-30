//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_TASK_HPP
#define GTD_TASK_HPP

#include <iostream>
#include <string_view>

#include "Completable.hpp"
#include "TaskContainer.hpp"
#include "GtdHelper.hpp"

namespace gtd {

class Task final : public Completable {

private:
	// hide from Project since Project has a ProjectType
    TaskContainer&              _gtdItems;
    TaskType					_taskType { TaskType::Parallel };
	std::optional<unique_id_t> 	_projectId { std::nullopt };

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

    // CTORS
    explicit Task(TaskContainer&,  std::string_view name = "");

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
