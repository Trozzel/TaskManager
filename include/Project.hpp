#ifndef PROJECTS_HPP
#define PROJECTS_HPP

#include <list>
#include <initializer_list>
#include <string_view>

#include "Completable.hpp"
#include "GtdHelper.hpp"
#include "ProjectContainer.hpp"

namespace gtd {
class Project final : public Completable
{
private:
    ProjectContainer&          _projects;
    ProjectType                _projectType{ProjectType::Parallel};
    std::optional<unique_id_t> _folderId{std::nullopt};
    std::vector<unique_id_t>   _taskIds{};
    bool                       _completeWithLast{true};
    std::string_view           _reviewSchedule{"0 0 * * 0"}; // 12a every Sunday

public:
    using gtd_category = project_tag;
    [[nodiscard]]
    static constexpr ProjectType
    strToProjectType( const std::string_view projectTypeStr ) noexcept {
        return projectTypeFromStr(projectTypeStr);
    }

    // CTORS
    /**************************************************************************/
    // DEFAULT
    explicit
    Project( ProjectContainer&, std::string_view name = "" );

    ~Project() final;

    [[nodiscard]]
    constexpr static const char*
        tableName() noexcept { return "projects"; }

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

    [[nodiscard]]
    std::ranges::range auto&&
    getTasks( std::ranges::range auto&& tasks ) const {
        return tasks |
            std::views::filter([this](auto&& task) {
                return task.projectId() == uniqueId().value_or(-1); // -1 ensures false
            });
    }

    // SETTERS
    /*************************************************************************/
    void
    setTaskIds( std::ranges::input_range auto&& taskIds ) {
        _taskIds = std::list(std::ranges::cbegin(taskIds), std::ranges::cend(taskIds));
    }

    void
    appendTaskIds( std::initializer_list<unique_id_t>&& taskIds );

    void
    appendTaskIds( std::ranges::range auto&& taskIds );

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
    setFolderId( unique_id_t folderId, bool update = true );

    void
    setCompleteWithLast( bool completeWithLast, bool update = true );

    void
    setReviewSchedule( std::string_view reviewSchedule, bool update = true );
};

//							HELPER FUNCTIONS
/*****************************************************************************/
template <typename Iter>
void
Project::appendTaskIds( Iter begin, Iter end ) {
    static_assert(std::is_integral_v<typename Iter::value_type>);
    for ( ; begin != end; ++begin ) {
        _taskIds.push_back(*begin);
    }
}

std::ostream&
operator<<( std::ostream& out, const Project& project );
} // namespace gtd

#endif // PROJECTS_HPP
