//
// Created by George Ford on 12/19/23.
//

#ifndef TASKCONTAINER_HPP
#define TASKCONTAINER_HPP

#include "CompleteableContainer.hpp"

namespace gtd {
class Task;

class TaskContainer/* final : public CompleteableContainer */
{
private:
    std::vector<Task> _tasks{};
    USMgr&            _usm;

public:
    using value_type = Task;
    using iterator = std::vector<Task>::iterator;
    using const_iterator = std::vector<Task>::const_iterator;
    using size_type = std::vector<Task>::size_type;
    using difference_type = std::vector<Task>::difference_type;

    [[nodiscard]] static const std::string&
    tableName();

    explicit
    TaskContainer( USMgr& );

    TaskContainer( const TaskContainer& other );

    ~TaskContainer();

    TaskContainer&
    operator=( const TaskContainer& );

    [[nodiscard]]
    auto
    begin();

    [[nodiscard]]
    auto
    cbegin() const;

    [[nodiscard]]
    auto
    end();

    [[nodiscard]]
    auto
    cend() const;

    [[nodiscard]] std::ranges::range auto&&
    getByProjectId( unique_id_t ) const;
};
} // namespace gtd

#endif //TASKCONTAINER_HPP
