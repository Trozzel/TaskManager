#include "Project.hpp"

using namespace std;

namespace gtd {


ProjectType Project::strToProjectType(const std::string& projectTypeStr) {
    return strToProjectType(projectTypeStr);
}

Project::Project(const std::string & name)
    : GtdBase(name)
{
}

inline ULL Project::contextId() const {
    return _contextId;
}

const std::string & Project::notes() const {
    return _notes;
}

const time_point_t & Project::deferred() const {
    return _deferred;
}

const time_point_t & Project::due() const {
    return _due;
}

ProjectType Project::projectType() const {
    return _projectType;
}

bool Project::isRepeating() const {
    return _isRepeating;
}

RepeatFrom Project::repeatFrom() const {
    return _repeatFrom;
}

const fs::directory_entry &Project::repeatFromPath() const {
    return _repeatFromPath;
}

const time_point_t &Project::getDeferred() const {
    return _deferred;
}

bool Project::isCompleteWithLast() const {
    return _completeWithLast;
}

const fs::directory_entry &Project::getRepeatFromPath() const {
    return _repeatFromPath;
}

void Project::setTaskIds(const std::initializer_list<ULL> & taskIds) {
    _taskIds = taskIds;
}

void Project::setTaskIds(const std::list<ULL> &taskIds) {
    _taskIds = taskIds;
}

void Project::appendTaskIds(const std::initializer_list<ULL> & taskIds) {
    for(auto it=taskIds.begin(); it != taskIds.end(); ++it) {
        _taskIds.push_back(*it);
    }
}

void Project::appendTaskId(ULL taskId) {
    _taskIds.push_back(taskId);
}

void Project::setContextId(ULL contextId) {
    _contextId = contextId;
}

void Project::setContextId(const std::string &contextIdStr) {
    _contextId = stoll(contextIdStr);
}

void Project::setNotes(const std::string &notes) {
    _notes = notes;
}

void Project::setDeferred(const time_point_t &deferred) {
    _deferred = deferred;
}

void Project::setDeferred(const std::string &deferredStr) {
    _deferred = strToTimePoint(deferredStr);
}

void Project::setIsRepeating(const std::string& isRepeating) {
    _isRepeating = static_cast<bool>(stoll(isRepeating));
}

void Project::setIsRepeating(bool isRepeating) {
    _isRepeating = isRepeating;
}

void Project::setRepeatFromPath(const std::string& dir) {
    _repeatFromPath.replace_filename(dir);
}

void Project::setRepeatFromPath(const fs::directory_entry& dir) {
    _repeatFromPath = dir;
}

void Project::setRepeatFrom(const std::string & repeatFromStr) {
    _repeatFrom = strToRepeatFrom(repeatFromStr);
}

void Project::setRepeatFrom(RepeatFrom repeatFrom) {
    _repeatFrom = repeatFrom;
}

void Project::setProjectType(const std::string & projectType) {
    _projectType = strToProjectType(projectType);
}

void Project::setProjectType(ProjectType projectType) {
    _projectType = projectType;
}

void Project::setCompleteWithLast(bool completeWithLast) {
    _completeWithLast = completeWithLast;
}

void Project::setCompleteWithLast(const std::string & completeWithLastStr) {
    _completeWithLast = static_cast<bool>(stoll(completeWithLastStr));
}

void Project::appendTaskIds(const std::list<ULL> &taskIds) {
    _taskIds.insert(_taskIds.end(), taskIds.begin(), taskIds.end());
}

void Project::appendTaskId(const std::string &taskIdStr) {
    _taskIds.push_back(stoll(taskIdStr));
}


void Project::setDue(const std::string &dueStr) {
    _due = strToTimePoint(dueStr);
}

void Project::setDue(const time_point_t &due) {
    _due = due;
}

std::ostream& operator<<(std::ostream& out, const Project& project) {
    // SEND BASE TO STREAM
    const auto* pBase = static_cast<const GtdBase*>(&project);
    out << *pBase;

    // SEND REMAINED TO STREAM
    out << project._notes << " " << fmt::format("{} ", project._deferred)
        << fmt::format("{} ", project._due)
        << projectTypeStr(project._projectType) << " "
        << ios::boolalpha << project._isRepeating << " "
        << repeatFromToStr(project._repeatFrom) << " "
        << project._repeatFromPath.path();

    return out;
}

} // namespace gtd
