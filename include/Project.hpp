#ifndef PROJECTS_HPP
#define PROJECTS_HPP

#include <string_view>
#include <vector>

#include "Completable.hpp"
#include "GtdHelper.hpp"

namespace gtd {

template<typename Gtd_t>
class GtdContainer;

class Project final : public Completable
{

public:
    using gtd_category = project_tag;

	// STATIC FUNCTIONS
	static constexpr const char*
	tableName() {
		return "projects";
	}
private:
    using sp_Container = std::shared_ptr<GtdContainer<Project>>;
    using wp_Container = std::weak_ptr<GtdContainer<Project>>;

    wp_Container               _projects;
    ProjectType                _projectType{ProjectType::Parallel};
    std::optional<unique_id_t> _folderId{std::nullopt};
    std::vector<unique_id_t>   _taskIds{};
    bool                       _completeWithLast{true};
    std::string                _reviewSchedule = {"0 0 * * 0"}; // 12a every Sunday

public:
    [[nodiscard]]
    static constexpr ProjectType
    strToProjectType( const std::string_view projectTypeStr ) noexcept {
        return projectTypeFromStr(projectTypeStr);
    }

    // CTORS
    /**************************************************************************/
    explicit Project( const sp_Container&, std::string_view name = "" );
    explicit Project( wp_Container, std::string_view name = "" );

    Project( const Project& ) = default;

    ~Project() override = default;

    // ASSIGNMENT OPERATORS
    /*************************************************************************/
    Project&
    operator=( const Project& );

    // COMPARISON OPERATORS
    /*************************************************************************/
    bool
    operator==( const Project& ) const;

    bool
    operator!=( const Project& ) const;

    // GETTERS
    /*************************************************************************/
    [[nodiscard]]
    constexpr ProjectType
    projectType() const noexcept {
        return _projectType;
    }

    [[nodiscard]]
    constexpr std::optional<unique_id_t>
    folderId() const noexcept {
        return _folderId;
    }

    [[nodiscard]]
    constexpr bool
    completeWithLast() const noexcept {
        return _completeWithLast;
    }

    [[nodiscard]]
    constexpr std::string_view
    reviewSchedule() const noexcept {
        return _reviewSchedule;
    }

	wp_Container
	container();

	const wp_Container
	container() const;

    // SETTERS
    /*************************************************************************/

    // OVERRIDE SETTERS
    /*************************************************************************/
    void
    setName( std::string_view name, bool update ) override;

    void
    setStatus( std::string_view status, bool update ) override;

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

    void
    setStatus( Status status, bool update ) override;

    void
    setParentId( unique_id_t id, bool update ) override;

    void
    setNotes( std::string_view notes, bool update ) override;

    void
    setContextId( unique_id_t id, bool update ) override;

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

    // PROJECT SETTERS
    /*************************************************************************/
    void
    setTaskIds( const std::initializer_list<unique_id_t>& taskIds );

    void
    setTaskIds( const std::vector<unique_id_t>& taskIds );

    template <typename Iter>
    void
    setTaskIds( Iter begin, Iter end )
        requires std::is_integral_v<typename Iter::value_type> {
        _taskIds.clear();
        _taskIds = std::vector<unique_id_t>(begin, end);
    }

    void
    appendTaskIds( const std::initializer_list<unique_id_t>& taskIds );

    void
    appendTaskIds( const std::vector<unique_id_t>& taskIds );

    template <typename Iter>
    void
    appendTaskIds( Iter begin, Iter end )
        requires std::is_integral_v<typename Iter::value_type> {
        _taskIds.insert(_taskIds.end(), begin, end);
    }

    void
    appendTaskId( unique_id_t taskId );

    void
    setProjectType( ProjectType projectType, bool update );

    void
    setProjectType( std::string_view projectType, bool update );

    void
    setFolderId( unique_id_t id, bool update );

    void
    setCompleteWithLast( bool completeWithLast, bool update );

    void
    setReviewSchedule( std::string_view reviewSchedule, bool update );

	void
	setContainer( sp_Container container );
	
	void
	setContainer( wp_Container container );
	
};

//							HELPER FUNCTIONS
/*****************************************************************************/
std::ostream&
operator<<( std::ostream& out, const Project& project );
} // namespace gtd

#endif // PROJECTS_HPP
