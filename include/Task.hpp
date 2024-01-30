//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_TASK_HPP
#define GTD_TASK_HPP

#include "Completable.hpp"
#include "GtdHelper.hpp"
#include <optional>
#include <string_view>

namespace gtd {

template<typename Gtd_t>
class GtdContainer;

class Task final : public Completable
{
public:
    using gtd_category = task_tag;
	
	// STATIC FUNCTIONS
	static constexpr const char*
	tableName() {
		return "tasks";
	}
private:
    using sp_Container = std::shared_ptr<GtdContainer<Task>>;
    using wp_Container = std::weak_ptr<GtdContainer<Task>>;

    wp_Container                    _tasks;
    TaskType                        _taskType{TaskType::Parallel};
    std::optional<unique_id_t>      _o_projectId{std::nullopt};

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
    explicit Task( const sp_Container&, std::string_view name = "" );
    explicit Task( wp_Container, std::string_view name = "" );
    Task( const Task& ) = default;

    // DTOR
    ~Task() override = default;

    // ASSIGMENT OPERATORS
    /*************************************************************************/
    Task&
    operator=( const Task& );

    // COMPARISON OPERATORS
    /*************************************************************************/
    bool
    operator==( const Task& ) const;

    bool
    operator!=( const Task& ) const;

    // OVERRIDE FUNCTIONS
    /*************************************************************************/
    void
    setParent( const GtdBase&, bool update ) override;

    void
    setParentId( std::optional<unique_id_t> id, bool update ) override;

    void
    setContextId( std::optional<unique_id_t> id, bool update ) override;

	void
	setContext( const Context& context, bool update ) override;

    void
    setFlagged( bool flagged, bool update ) override;

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

	wp_Container
	container();

	const wp_Container
	container() const;

    // OVERRIDE METHODS: Must update UpdateStack
    /*************************************************************************/
    void
    setStatus( std::string_view status, bool update ) override;

    void
    setStatus( Status status, bool update ) override;

    void
    setParentId( unique_id_t id, bool update ) override;

    void
    setNotes( std::string_view notes, bool update ) override;

    void
    setContextId( unique_id_t contextId, bool update ) override;

    void
    setDeferred( time_point_t deferred, bool update ) override;

    void
    setDeferred( std::string_view deferred, bool update ) override;

    void
    setDue( time_point_t tp, bool update ) override;

    void
    setDue( std::string_view due_str, bool update ) override;

    void
    setIsRepeating( int isRepeating, bool update ) override;

    void
    setFlagged( int flagged, bool update ) override;

    void
    setRepeatFrom( RepeatFrom repeatFrom, bool update ) override;

    void
    setRepeatFrom( std::string_view rptFromStr, bool update ) override;

    void
    setRepeatSchedule( std::string_view schedule, bool update ) override;
	
    // NON-VIRTUAL Task METHODS
    /*************************************************************************/
    void
    setProjectId( unique_id_t projectId, bool update );

    void
    setProject( const Project& , bool update );

    void
    setTaskType( std::string_view taskType, bool update );

    void
    setTaskType( TaskType taskType, bool update );

	void
	setContainer( sp_Container container );
	
	void
	setContainer( wp_Container container );
	
};
} // namespace gtd

//operator<<(std::ostream &out, const gtd::Task &task);

#endif //GTD_TASK_HPP
