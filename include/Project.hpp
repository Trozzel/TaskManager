#ifndef PROJECTS_HPP
#define PROJECTS_HPP

#include <string>
#include <list>
#include <initializer_list>

#include <fmt/format.h>
#include <string_view>
#include <type_traits>

#include "GtdBase.hpp"
#include "Task.hpp"
#include "CompletableBase.hpp"
#include "GtdHelper.hpp"

namespace gtd {

class Project final : public CompletableBase {

private:
	ProjectType			 _projectType {ProjectType::Parallel};
	LL_t				 _folderId {-1};
    std::list<LL_t>      _taskIds {};
    bool                 _completeWithLast { true };
	std::string_view     _reviewSchedule = {"0 0 * * 0"}; // 12a every Sunday

public:
    // STATIC FUNCTIONS
    static constexpr ProjectType 
	strToProjectType(std::string_view taskProjectStr) noexcept;

    // CTORS
    /**************************************************************************/
    // DEFAULT
    Project(std::string_view name = "");

    ~Project() final = default;

    // GETTERS
    [[nodiscard]]
	constexpr ProjectType
	projectType() const noexcept { return _projectType; }

	[[nodiscard]]
	constexpr LL_t
	folderId() const noexcept { return _folderId; }

    [[nodiscard]] 
	constexpr bool 
	completeWithLast() const noexcept { return _completeWithLast; }

	[[nodiscard]]
	constexpr std::string_view
	reviewSchedule() noexcept { return _reviewSchedule; }

    // SETTERS
	void 
	setTaskIds(const std::initializer_list<LL_t> & taskIds);
	void 
	setTaskIds(const std::list<LL_t> & taskIds);
    template<typename Iter>
    void 
	setTaskIds(Iter begin, Iter end);

    void 
	appendTaskIds(const std::initializer_list<LL_t> & taskIds);
	void 
	appendTaskIds(const std::list<LL_t> & taskIds);
    template<typename Iter>
    void 
	appendTaskIds(Iter begin, Iter end);

    void 
	appendTaskId(LL_t taskId);
    void 
	appendTaskId(const std::string& taskIdStr);

    constexpr void 
	setProjectType(ProjectType projectType) noexcept {
		_projectType = projectType;
	}
    void 
	setProjectType(std::string_view projectType);

	constexpr void
	setFolderId(LL_t folderId) noexcept {
		_folderId = folderId;
	}

    constexpr void 
	setCompleteWithLast(bool completeWithLast) noexcept {
		_completeWithLast = completeWithLast;
	}
    void 
	setCompleteWithLast(const std::string& completeWithLastStr);
    void 
	setCompleteWithLast(const int completeWithLast);

	constexpr void
	setReviewSchedule(std::string_view reviewSchedule) noexcept {
		_reviewSchedule = reviewSchedule;
	}

    friend std::ostream& 
	operator<<(std::ostream& out, const Project& project);
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
const auto
getProject_it(const gtd::Task& task, const Projects_vec& projects);

} // namespace gtd

#endif // PROJECTS_HPP
