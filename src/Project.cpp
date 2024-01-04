#include "Project.hpp"
#include "Task.hpp"
#include "Completable.hpp"
#include "GtdBase.hpp"
#include "GtdHelper.hpp"

using namespace std;

namespace gtd {

static_assert(IsProject<Project>);

// CTOR
Project::Project( ProjectContainer& gtdItems, std::string_view name ) :
    Completable(gtdItems, name),
    _projects(gtdItems) {
    _projects.push_back(this);
}

Project::~Project() = default;

// GETTERS
/*****************************************************************************/
std::ranges<pTask_t>
Project::getTasks( const TaskContainer& tasks ) const {
    return std::find_if(tasks.cbegin(), tasks.cend(),
                        [this]( const TaskContainer::const_iterator& pTask ) {
                            return (*pTask)->parentId() == this->uniqueId();
                        });
}

// SETTERS
/*****************************************************************************/
void
Project::setTaskIds( std::ranges::input_range auto&& taskIds ) {
    _taskIds = std::list<Task>(taskIds.begin(), taskIds.end());
}

void
Project::appendTaskIds( std::ranges::range auto&& taskIds ) {
    _taskIds.insert(_taskIds.end(), taskIds.begin(), taskIds.end());
}

void
Project::appendTaskIds( std::initializer_list<unique_id_t>&& taskIds ) {
    for ( unsigned long long taskId : taskIds ) {
        _taskIds.push_back(taskId);
    }
}

void
Project::appendTaskId( unique_id_t taskId ) {
    _taskIds.push_back(taskId);
}

void
Project::setProjectType( ProjectType projectType, bool update ) {
    _projectType = projectType;
    pushToUpdateStack("projectType", projectTypeStr(_projectType), update);
}

void
Project::setProjectType( std::string_view projectType, bool update ) {
    _projectType = strToProjectType(projectType);
    pushToUpdateStack("projectType", projectTypeStr(_projectType), update);
}

void
Project::setFolderId( unique_id_t id, const bool update ) {
    _folderId = id;
    pushToUpdateStack("folderId", folderId(), update);
}

void
Project::setCompleteWithLast( bool completeWLast, const bool update ) {
    _completeWithLast = completeWLast;
    pushToUpdateStack("completeWithLast", completeWithLast(), update);
}

void
Project::setReviewSchedule( std::string_view review, const bool update ) {
    _reviewSchedule = review;
    pushToUpdateStack("reviewSchedule", repeatSchedule(), update);
}

std::ostream&
operator<<( std::ostream& out, const Project& project ) {
    // SEND BASE TO STREAM
    const auto* pBase = static_cast<const GtdBase*>(&project);
    out << *pBase;

    // SEND REMAINED TO STREAM
    out << *project.notes() << " "
            << *project.deferredStr()
            << *project.dueStr() << " "
            << projectTypeStr(project.projectType()) << " "
            << ios::boolalpha << project.isRepeating() << " "
            << project.repeatFromStr() << " ";

    return out;
}
} // namespace gtd
