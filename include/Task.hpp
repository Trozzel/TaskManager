//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_TASK_HPP
#define GTD_TASK_HPP

#include "Completable.hpp"
#include "GtdHelper.hpp"
#include <__concepts/same_as.h>

namespace gtd {
class Task final : public Completable
{
public:
    using gtd_category = task_tag;

private:
    using pContainer = std::shared_ptr<GtdContainer<Task>>;
    pContainer _tasks{nullptr};

    TaskType                   _taskType{TaskType::Parallel};
    std::optional<unique_id_t> _o_projectId{std::nullopt};

public:
    // STATIC FUNCTIONS
    static constexpr
    TaskType
    strToTaskType( const std::string_view taskTypeStr ) noexcept {
        TaskType taskType;
        if ( taskTypeStr == "Parallel" ) {
            taskType = TaskType::Parallel;
        }
        else if ( taskTypeStr == "Sequential" ) {
            taskType = TaskType::Sequential;
        }
        else {
            fmt::print(stderr, "Incorrect Task Type String: '{}'\n", taskTypeStr);
            taskType = TaskType::Parallel;
        }
        return taskType;
    }

    // CTORS
    /*************************************************************************/
    explicit
    Task( pContainer, std::string_view name = "" );
    explicit
    Task( GtdContainer<Task>*, std::string_view name = "");
    Task( const Task& ) = default;
    Task( Task&& ) noexcept;

    // DTOR
    ~Task() override = default;

    // ASSIGMENT OPERATORS
    /*************************************************************************/
    Task&
    operator=( const Task& );
    Task&
    operator=( Task&& ) noexcept;

    // COMPARISON OPERATORS
    /*************************************************************************/
    bool
    operator==( const Task& ) const;

    bool
    operator!=( const Task& ) const;

    // GETTERS
    /*************************************************************************/
    [[nodiscard]] [[maybe_unused]]
    constexpr std::optional<unique_id_t>
    projectId() const noexcept {
        return _o_projectId;
    }

    [[nodiscard]] [[maybe_unused]]
    constexpr TaskType
    taskType() const noexcept {
        return _taskType;
    }

    // SETTERS
    /*************************************************************************/
    // 1. NON-VIRTUAL Task METHODS
    /*************************************************************************/
    void
    setProjectId( unique_id_t projectId, bool update = true );

    void
    setTaskType( std::string_view taskType, bool update = true );

    void
    setTaskType( TaskType taskType, bool update = true );

    // 2. OVERRIDE METHODS: Must update UpdateStack
    /*************************************************************************/
    void
    setStatus( std::string_view status, bool update = true ) override;

    void
    setStatus( Status status, bool update = true ) override;

    void
    setParentId( unique_id_t id, bool update = true ) override;

    void
    setNotes( std::string_view notes, bool update = true ) override;

    void
    setContextId( unique_id_t contextId, bool update = true ) override;

    void
    setDeferred( time_point_t deferred, bool update = true ) override;

    void
    setDeferred( std::string_view deferred, bool update = true ) override;

    void
    setDue( time_point_t tp, bool update = true ) override;

    void
    setDue( std::string_view due_str, bool update = true ) override;

    void
    setIsRepeating( int isRepeating, bool update = true ) override;

    void
    setFlagged( int flagged, bool update = true ) override;

    void
    setRepeatFrom( RepeatFrom repeatFrom, bool update = true ) override;

    void
    setRepeatFrom( std::string_view rptFromStr, bool update = true ) override;

    void
    setRepeatSchedule( std::string_view schedule, bool update = true ) override;
};
} // namespace gtd

//operator<<(std::ostream &out, const gtd::Task &task);

#endif //GTD_TASK_HPP
