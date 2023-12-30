//
// Created by George Ford on 12/19/23.
//

#ifndef TASKCONTAINER_HPP
#define TASKCONTAINER_HPP

#include "CompleteableContainer.hpp"

namespace gtd {
class Task;
using pTask_t = std::unique_ptr<Task>;

class TaskContainer final : public CompleteableContainer
{
private:
    std::vector<pTask_t> _gtdItems;

public:
    using value_type = std::vector<pTask_t>::value_type;
    using iterator = std::vector<pTask_t>::iterator;
    using const_iterator = std::vector<pTask_t>::const_iterator;
    using size_type = std::vector<pTask_t>::size_type;
    using difference_type = std::vector<pTask_t>::difference_type;

    explicit
    TaskContainer( USMgr& );

    TaskContainer( const TaskContainer& other ) :
        CompleteableContainer(other),
        _gtdItems(other._gtdItems) {}

    ~TaskContainer() override;

    TaskContainer&
    operator=( const TaskContainer& );

    [[nodiscard]] const std::string&
    tableName() const override;

    [[nodiscard]]
    auto
    begin() override;

    [[nodiscard]]
    auto
    cbegin() const override;

    [[nodiscard]]
    auto
    end() override;

    [[nodiscard]]
    auto
    cend() const override;

    [[nodiscard]] std::ranges<pTask_t>
    getByProjectId( unique_id_t ) const;
};

} // namespace gtd

#endif //TASKCONTAINER_HPP
