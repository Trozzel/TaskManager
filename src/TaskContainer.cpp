//
// Created by George Ford on 12/19/23.
//

#include "TaskContainer.hpp"

#include <Task.hpp>

namespace gtd {

TaskContainer::TaskContainer( USMgr& usm ) :
    _usm(usm) {}

TaskContainer::~TaskContainer() = default;

// STATIC - return the table name
const std::string&
TaskContainer::tableName() {
    const static std::string table = "tasks";
    return table;
}

std::ranges::range auto&&
TaskContainer::getByProjectId( unique_id_t id ) const {
    return _tasks |
            std::views::filter([id]( const auto& pTask ) {
                return *pTask->projectId() == id;
            });
}

auto
TaskContainer::begin() {
    return _tasks.begin();
}

auto
TaskContainer::cbegin() const {
    return _tasks.cbegin();
}

auto
TaskContainer::end() {
    return _tasks.end();
}

auto
TaskContainer::cend() const {
    return _tasks.cend();
}
} // namespace gtd
