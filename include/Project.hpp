#ifndef PROJECTS_HPP
#define PROJECTS_HPP

#include <string>
#include <list>
#include <initializer_list>
#include <string_view>

#include "Completable.hpp"
#include "GtdHelper.hpp"
#include "ProjectContainer.hpp"
#include "TaskContainer.hpp"

namespace gtd {

class Project final : public Completable {

private:
    ProjectContainer&           _gtdItems;
	ProjectType					_projectType { ProjectType::Parallel };
	std::optional<unique_id_t>  _folderId { std::nullopt };
    std::list<unique_id_t>      _taskIds {};
    bool						_completeWithLast { true };
	std::string_view     		_reviewSchedule {"0 0 * * 0"}; // 12a every Sunday

public:
	[[nodiscard]]
    static constexpr ProjectType 
	strToProjectType(std::string_view projectTypeStr) noexcept {
		return projectTypeFromStr(projectTypeStr);
	}

    // CTORS
    /**************************************************************************/
    // DEFAULT
    explicit Project(ProjectContainer&, std::string_view name = "");

    ~Project() final;

    // GETTERS
	/*************************************************************************/
    [[nodiscard]]
	constexpr ProjectType
	projectType() const noexcept { return _projectType; }

	[[nodiscard]]
	constexpr std::optional<unique_id_t>
	folderId() const noexcept { return _folderId; }

    [[nodiscard]] 
	constexpr bool
	completeWithLast() const noexcept { return _completeWithLast; }

	[[nodiscard]]
	constexpr std::string_view
	reviewSchedule() const noexcept { return _reviewSchedule; }

    [[nodiscard]]
    std::ranges<pTask_t>
    getTasks(const TaskContainer&) const;

    // SETTERS
	/*************************************************************************/
	void 
	setTaskIds(const std::initializer_list<unique_id_t> & taskIds);

	void 
	setTaskIds(const std::list<unique_id_t> & taskIds);

    template<typename Iter>
    void 
	setTaskIds(Iter begin, Iter end);

    void 
	appendTaskIds(const std::initializer_list<unique_id_t> & taskIds);

	void 
	appendTaskIds(const std::list<unique_id_t> & taskIds);

    template<typename Iter>
    void 
	appendTaskIds(Iter begin, Iter end);

    void 
	appendTaskId(unique_id_t taskId);

    void 
	setProjectType(ProjectType projectType, bool update = true);

    void 
	setProjectType(std::string_view projectType, bool update = true);

	void
	setFolderId(unique_id_t folderId, bool update = true);

    void 
	setCompleteWithLast(bool completeWithLast, bool update = true);

	void
	setReviewSchedule(std::string_view reviewSchedule, bool update = true);
};

//							HELPER FUNCTIONS
/*****************************************************************************/

/// \brief Associate given project with its tasks (Project::_taskIds)
template<typename Iter>
void Project::setTaskIds(Iter begin, Iter end) {
	static_assert(std::is_integral_v<typename Iter::value_type>);
    _taskIds.clear();
    for(; begin != end; ++begin) {
        _taskIds.push_back(*begin);
    }
}

/// \brief Append tasks to the Project::_taskIds
template<typename Iter>
void Project::appendTaskIds(Iter begin, Iter end) {
	static_assert(std::is_integral_v<typename Iter::value_type>);
    for(; begin != end; ++begin) {
        _taskIds.push_back(*begin);
    }
}

/// \brief Get gtd::Project object from task
/// \note Must check for it == projects.end() on call
using Projects_vec = std::vector<const gtd::Project>;
auto
getProject_it(const Task& task, const Projects_vec& projects);

std::ostream& 
operator<<(std::ostream& out, const Project& project);
} // namespace gtd

#endif // PROJECTS_HPP
