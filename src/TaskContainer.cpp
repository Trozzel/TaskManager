//
// Created by George Ford on 12/19/23.
//

#include "TaskContainer.hpp"

#include <Task.hpp>

namespace gtd {

TaskContainer::TaskContainer( USMgr& usm ) :
    CompleteableContainer(usm) {}

TaskContainer::~TaskContainer() = default;

const std::string&
TaskContainer::tableName() const {
    const static std::string table = "tasks";
    return table;
}

std::ranges<pTask_t>
TaskContainer::getByProjectId( unique_id_t id ) const {
    return _gtdItems |
            std::views::filter([id]( const pTask_t& pTask ) {
                return *pTask->projectId() == id;
            });
}

auto
TaskContainer::begin() {
    return _gtdItems.begin();
}

auto
TaskContainer::cbegin() const {
    return _gtdItems.cbegin();
}

auto
TaskContainer::end() {
    return _gtdItems.end();
}

auto
TaskContainer::cend() const {
    return _gtdItems.cend();
}
} // namespace gtd
