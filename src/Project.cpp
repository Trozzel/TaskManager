#include "Project.hpp"
#include "GtdHelper.hpp"
#include <string_view>

using namespace std;

namespace gtd {


Project::Project(std::string_view name)
    : CompletableBase(name)
{
}

// STATIC FUNCTIONS
constexpr ProjectType 
Project::strToProjectType(std::string_view projectTypeStr) noexcept {
    return strToProjectType(projectTypeStr);
}

// SETTERS
void 
Project::setTaskIds(const std::initializer_list<LL_t> & taskIds) {
    _taskIds = taskIds;
}

void 
Project::setTaskIds(const std::list<LL_t> &taskIds) {
    _taskIds = taskIds;
}

void 
Project::appendTaskIds(const std::initializer_list<LL_t> & taskIds) {
    for(auto it=taskIds.begin(); it != taskIds.end(); ++it) {
        _taskIds.push_back(*it);
    }
}

void 
Project::appendTaskId(LL_t taskId) {
    _taskIds.push_back(taskId);
}

void 
Project::setProjectType(std::string_view projectType) {
    _projectType = strToProjectType(projectType);
}

void 
Project::setCompleteWithLast(const std::string & completeWithLastStr) {
    _completeWithLast = static_cast<bool>(stoll(completeWithLastStr));
}

void 
Project::setCompleteWithLast(const int completeWithLastStr) {
    _completeWithLast = static_cast<bool>(completeWithLastStr);
}

void 
Project::appendTaskIds(const std::list<LL_t> &taskIds) {
    _taskIds.insert(_taskIds.end(), taskIds.begin(), taskIds.end());
}

void 
Project::appendTaskId(const std::string &taskIdStr) {
    _taskIds.push_back(stoll(taskIdStr));
}

const auto
getProject_it(const gtd::Task& task, const Projects_vec& projects) {
	auto projectId = task.projectId();
	auto it = std::find_if(projects.begin(), projects.end(), 
			[projectId](const gtd::Project& project) {
			return project.uniqueId() == projectId;
	});
	return it;
}

std::ostream& 
operator<<(std::ostream& out, const Project& project) {
    // SEND BASE TO STREAM
    const auto* pBase = static_cast<const GtdBase*>(&project);
    out << *pBase;

    // SEND REMAINED TO STREAM
    out << project._notes << " " << fmt::format("{} ", project._deferred)
        << fmt::format("{} ", project.due())
        << projectTypeStr(project.projectType()) << " "
        << ios::boolalpha << project.isRepeating() << " "
        << repeatFromToStr(project._repeatFrom) << " ";

    return out;
}

} // namespace gtd
