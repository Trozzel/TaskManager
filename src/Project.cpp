//
// Created by George Ford on 1/28/22.
//
#include <algorithm>

#include "Project.hpp"

#include <utility>

using namespace std;

namespace gtd {

Project::Project(string projectName,
                 string notes,
                 const Folder* folder,
                 Status status, ProjectType projectType,
                 list<const Context*> contexts,
				 list<const Task*> tasks,
                 dt::RepeatingCTime *deferred,
                 dt::RepeatingCTime *due) :
        _projectName(move(projectName)), _notes(move(notes)),
        _folder(folder), _status(status), _projectType(projectType),
        _contexts(move(contexts)), _tasks(move(tasks)), _deferred(deferred),
        _due(due)
{
    _created = make_unique<dt::CTime>();
    updateModified();
}

std::string Project::statusString() const {
    return gtd::statusString(_status);
}

std::string Project::projectTypeString() const {
    return gtd::projectTypeString(_projectType);
}

std::list<const Context*> Project::contexts() {
    return _contexts;
}

std::list<const Task*> Project::tasks() {
	return _tasks;
}

void Project::setContexts(const initializer_list<const Context *>& contexts) {
    _contexts = contexts;
    updateModified();
}

void Project::setContexts(const list<const Context *> &contexts) {
    _contexts = contexts;
    updateModified();
}

const Context *Project::removeContext(const Context *context) {
    auto itContext = std::find(_contexts.begin(),
                               _contexts.end(),
                               context);
    _contexts.remove(context);
    updateModified();
    return *itContext;
}

void Project::setTasks(const std::initializer_list<const Task*>& tasks)
{
	_tasks = tasks;
	updateModified();
}

void Project::setTasks(const std::list<const Task*> tasks)
{
	_tasks = tasks;
	updateModified();
}

const Task* Project::removeTask(const Task* task)
{
	auto itTask = std::find(_tasks.begin(), _tasks.end(), task);
	_tasks.remove(task);
	return *itTask;
}



void Project::markAsComplete() {
    setStatus(Status::Completed);
    _completed = make_unique<dt::CTime>();
}

} // namespace gtd
