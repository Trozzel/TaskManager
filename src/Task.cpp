//
// Created by George Ford on 1/28/22.
//
#include <algorithm>

#include "Task.hpp"

using namespace std;

namespace gtd {

// STRING TO PROJECT TYPE
TaskType Task::strToTaskType(const string &taskTypeStr) {
    TaskType pt;
    if(taskTypeStr == "parallel") {
        pt = TaskType::Parallel;
    }
    else if(taskTypeStr == "sequential"){
        pt = TaskType::Sequential;
    }
    else {
        fmt::print(stderr, "Incorrect Task Type String: '{}'\n", taskTypeStr);
        pt = TaskType::Parallel;
    }
    return pt;
}

// DEFAULT CTOR
Task::Task(const string &name) :
    GtdBase(name)
{
}

const string &Task::notes() const {
    return _notes;
}

const time_point_t &Task::deferred() const {
    return _deferred;
}

const time_point_t &Task::due() const {
    return _due;
}

TaskType Task::taskType() const {
    return _taskType;
}

bool Task::isIsRepeating() const {
    return _isRepeating;
}

RepeatFrom Task::repeatFrom() const {
    return _repeatFrom;
}

const fs::directory_entry &Task::repeatFromPath() const {
    return _repeatFromPath;
}

ULL Task::projectId() const {
	return _projectId;
}

void Task::setProjectId(ULL projectId) {
	_projectId = projectId;
}

void Task::setProjectId(const std::string & projectIdStr){
	_projectId = stoll(projectIdStr);
}


void Task::setNotes(const string &notes) {
    _notes = notes;
}

void Task::setDeferred(const time_point_t &deferred) {
    _deferred = deferred;
}

void Task::setDeferred(const string &deferredStr) {
    _deferred = strToTimePoint(deferredStr);
}

void Task::setDue(const time_point_t &due) {
    _due = due;
}

void Task::setDue(const string &dueStr) {
    _due = strToTimePoint(dueStr);
}

void Task::setTaskType(TaskType taskType) {
    _taskType = taskType;
}

void Task::setTaskType(const string &taskType) {
    _taskType = strToTaskType(taskType);
}

void Task::setIsRepeating(bool isRepeating) {
    _isRepeating = isRepeating;
}

void Task::setIsRepeating(const string& isRepeating) {
    _isRepeating = stoll(isRepeating) > 0;
}

void Task::setRepeatFrom(RepeatFrom repeatFrom) {
    _repeatFrom = repeatFrom;
}

void Task::setRepeatFrom(const string &repeatFromStr) {
    _repeatFrom = strToRepeatFrom(repeatFromStr);
}

void Task::setRepeatFromPath(const fs::directory_entry &dir) {
    _repeatFromPath = dir;
}

void Task::setRepeatFromPath(const string &dir) {
    _repeatFromPath = fs::directory_entry(dir);
}

void Task::setContextId(ULL contextId) {
    _contextId = contextId;
}

void Task::setContextId(const string &contextIdStr) {
    _contextId = stoll(contextIdStr);
}

ULL Task::contextId() const {
    return _contextId;
}

const time_point_t &Task::getDeferred() const {
    return _deferred;
}

const fs::directory_entry &Task::getRepeatFromPath() const {
    return _repeatFromPath;
}

std::ostream& operator<<(std::ostream& out, const Task& task) {
    // SEND BASE TO STREAM
    const auto* pBase = static_cast<const GtdBase*>(&task);
    out << *pBase;

    // SEND REMAINED TO STREAM
    out << task._notes << " " << fmt::format("{} ", task._deferred)
        << fmt::format("{} ", task._due)
        << taskTypeString(task._taskType) << " "
        << ios::boolalpha << task._isRepeating << " "
        << repeatFromToStr(task._repeatFrom) << " "
        << task._repeatFromPath.path();

    return out;
}

} // namespace gtd
