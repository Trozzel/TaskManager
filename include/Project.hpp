#ifndef PROJECTS_HPP
#define PROJECTS_HPP

#include <string_view>

#include "Completable.hpp"
#include "GtdHelper.hpp"

namespace gtd {
class Project final : public Completable
{
public:
    using gtd_category = project_tag;

private:
    using pContainer = std::shared_ptr<GtdContainer<Project>>;

    pContainer                 _projects;
    ProjectType                _projectType{ProjectType::Parallel};
    std::optional<unique_id_t> _folderId{std::nullopt};
    std::vector<unique_id_t>   _taskIds{};
    bool                       _completeWithLast{true};
    std::string_view           _reviewSchedule = {"0 0 * * 0"}; // 12a every Sunday

public:
    // STATIC FUNCTIONS
    /*************************************************************************/
    constexpr static
    std::string_view
    tableName() noexcept {
        return "projects";
    }

    [[nodiscard]]
    static constexpr ProjectType
    strToProjectType( const std::string_view projectTypeStr ) noexcept {
        return projectTypeFromStr(projectTypeStr);
    }

    // CTORS
    /**************************************************************************/
    // DEFAULT
    explicit
    Project( pContainer, std::string_view name = "" );
    explicit
    Project( GtdContainer<Project>*, std::string_view name = "" );

    Project(const Project&);
    Project(Project&&) noexcept;

    ~Project() override = default;

    // ASSIGNMENT OPERATORS
    /*************************************************************************/
    Project&
    operator=( const Project& );

    Project&
    operator=( Project&& ) noexcept;

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

    // SETTERS
    /*************************************************************************/

    // OVERRIDE SETTERS
    /*************************************************************************/
    void
    setName( std::string_view name, bool update = true ) override;

    void
    setStatus( std::string_view status, bool update = true ) override;

    void
    setStatus( Status status, bool update = true ) override;

    void
    setParentId( unique_id_t id, bool update = true ) override;

    void
    setNotes( std::string_view notes, bool update = true ) override;

    void
    setContextId( unique_id_t id, bool update = true ) override;

    void
    setDeferred( time_point_t deferred, bool update = true ) override;

    void
    setDeferred( std::string_view deferred, bool update = true ) override;

    void
    setDue( time_point_t tp, bool update = true ) override;

    void
    setDue( std::string_view due_str, bool update = true ) override;

    void
    setTaskType( const std::string& taskType, bool update = true ) override;

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

    // PROJECT SETTERS
    /*************************************************************************/
    void
    setTaskIds( const std::initializer_list<unique_id_t>& taskIds );

    void
    setTaskIds( const std::vector<unique_id_t>& taskIds );

    template <typename Iter>
    void
    setTaskIds( Iter begin, Iter end );

    void
    appendTaskIds( const std::initializer_list<unique_id_t>& taskIds );

    void
    appendTaskIds( const std::vector<unique_id_t>& taskIds );

    template <typename Iter>
    void
    appendTaskIds( Iter begin, Iter end );

    void
    appendTaskId( unique_id_t taskId );

    void
    setProjectType( ProjectType projectType, bool update = true );

    void
    setProjectType( std::string_view projectType, bool update = true );

    void
    setFolderId( unique_id_t id, bool update = true );

    void
    setCompleteWithLast( bool completeWithLast, bool update = true );

    void
    setReviewSchedule( std::string_view reviewSchedule, bool update = true );
};

//							HELPER FUNCTIONS
/*****************************************************************************/
std::ostream&
operator<<( std::ostream& out, const Project& project );
} // namespace gtd

#endif // PROJECTS_HPP
