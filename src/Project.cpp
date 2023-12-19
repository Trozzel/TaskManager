#include "Project.hpp"
#include "CompletableBase.hpp"
#include "GtdBase.hpp"
#include "GtdHelper.hpp"
#include "UpdateStack.hpp"

using namespace std;

namespace gtd {
Project::Project( USMgr& updateStackMgr, std::string_view name ) :
    CompletableBase(updateStackMgr, name) {}

// SETTERS
/*****************************************************************************/
void
Project::setTaskIds( const std::initializer_list<unique_id_t>& taskIds ) {
    _taskIds = taskIds;
}

void
Project::setTaskIds( const std::list<unique_id_t>& taskIds ) {
    _taskIds = taskIds;
}

void
Project::appendTaskIds( const std::list<unique_id_t>& taskIds ) {
    _taskIds.insert(_taskIds.end(), taskIds.begin(), taskIds.end());
}

void
Project::appendTaskIds( const std::initializer_list<unique_id_t>& taskIds ) {
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
    if ( update ) {
        const auto pUpdateStack = _updateStackMgr.getUpdateStack();
        pUpdateStack->push(*this, "projectType");
    }
}

void
Project::setProjectType( std::string_view projectType, bool update ) {
    _projectType = strToProjectType(projectType);
    if ( update ) {
        const auto pUpdateStack = _updateStackMgr.getUpdateStack();
        pUpdateStack->push(*this, "projectType");
    }
}

void
Project::setFolderId( unique_id_t folderId, bool update ) {
    _folderId = folderId;
    if ( update ) {
        const auto pUpdateStack = _updateStackMgr.getUpdateStack();
        pUpdateStack->push(*this, "folderId");
    }
}

void
Project::setCompleteWithLast( bool completeWithLast, bool update ) {
    _completeWithLast = completeWithLast;
    if ( update ) {
        const auto pUpdateStack = _updateStackMgr.getUpdateStack();
        pUpdateStack->push(*this, "completeWithLast");
    }
}

void
Project::setReviewSchedule( std::string_view reviewSchedule, bool update ) {
    _reviewSchedule = reviewSchedule;
    if ( update ) {
        const auto pUpdateStack = _updateStackMgr.getUpdateStack();
        pUpdateStack->push(*this, "reviewSchedule");
    }
}

auto
getProject_it( const gtd::Task& task, const Projects_vec& projects ) {
    auto       projectId = task.projectId();
    const auto it        = std::ranges::find_if(
        projects.cbegin(), projects.cend(),
        [projectId]( const gtd::Project& project ) {
            return project.uniqueId() == projectId;
        });
    return it;
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
