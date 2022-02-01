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
                 Status status, ProjectType projectType,
                 list<const Context *> contexts,
                 dt::RepeatingCTime *deferred,
                 dt::RepeatingCTime *due) :
        _projectName(move(projectName)), _notes(move(notes)),
        _status(status), _projectType(projectType),
        _contexts(move(contexts)), _deferred(deferred),
        _due(due)
{
    _created = make_unique<dt::CTime>();
    updateModified();
}

Project::Project(string projectName,
                 string notes,
                 Status status,
                 ProjectType projectType,
                 initializer_list<const Context *> contexts,
                 dt::RepeatingCTime *deferred,
                 dt::RepeatingCTime *due) :
        _projectName(move(projectName)), _notes(move(notes)),
        _status(status), _projectType(projectType), _contexts(contexts),
        _deferred(deferred), _due(due)
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

std::list<const Context *> Project::contexts() {
    return _contexts;
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
    _contexts.remove(context);
    updateModified();
}

void Project::markAsComplete() {
    setStatus(Status::Completed);
    _completed = make_unique<dt::CTime>();
}

} // namespace gtd