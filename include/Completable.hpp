//
// Created by George Ford on 1/28/22.
//

#ifndef COMPLETABLE_HPP_
#define COMPLETABLE_HPP_

#include "GtdBase.hpp"

namespace gtd {
class Completable : public GtdBase
{
public:
    using gtd_category = completable_tag;

protected:
    std::optional<unique_id_t>  _o_contextId{std::nullopt};
    std::optional<time_point_t> _o_deferred{std::nullopt};
    std::optional<time_point_t> _o_due{std::nullopt};
    bool                        _isRepeating{false};
    bool                        _flagged{false};
    RepeatFrom                  _repeatFrom{RepeatFrom::Due};
    std::string                 _repeatSchedule{"30 16 * * *"}; // Every day at 4:30pm

public:
    // CTORS
    /*************************************************************************/
    explicit
    Completable( std::string_view name = "" );
    Completable( const Completable& ) = default;
    Completable( Completable&& ) noexcept;

    ~Completable() override = 0;

    // ASSIGMENT OPERATORS
    /*************************************************************************/
    Completable&
    operator=( const Completable& ) = default;
    Completable&
    operator=( Completable&& ) noexcept;

    // GETTERS
    // COMPARISON OPERATORS
    /*************************************************************************/
    bool
    operator==( const Completable& ) const;

    bool
    operator!=( const Completable& ) const;

    /*************************************************************************/
    [[nodiscard]] [[maybe_unused]]
    constexpr std::optional<unique_id_t>
    contextId() const noexcept {
        return _o_contextId;
    }

    [[nodiscard]] [[maybe_unused]]
    constexpr std::optional<time_point_t>
    deferred() const noexcept {
        return _o_deferred;
    }

    [[nodiscard]] [[maybe_unused]]
    std::optional<std::string>
    deferredStr() const;

    [[nodiscard]]
    constexpr std::optional<time_point_t>
    due() const noexcept {
        return _o_due;
    }

    [[nodiscard]]
    std::optional<std::string>
    dueStr() const;

    [[nodiscard]]
    constexpr bool
    isRepeating() const noexcept {
        return _isRepeating;
    }

    [[nodiscard]] [[maybe_unused]]
    constexpr bool
    flagged() const noexcept {
        return _flagged;
    }

    [[nodiscard]]
    constexpr RepeatFrom
    repeatFrom() const noexcept {
        return _repeatFrom;
    }

    [[nodiscard]]
    constexpr std::string_view
    repeatFromStr() const {
        return repeatFromToStr(_repeatFrom);
    }

    [[nodiscard]]
    constexpr std::string_view
    repeatSchedule() const noexcept {
        return _repeatSchedule;
    }

    // SETTERS
    /*************************************************************************/
    [[maybe_unused]]
    virtual void
    setContextId( unique_id_t contextId, bool update );

    virtual void
    setDeferred( time_point_t deferred, bool update );
    [[maybe_unused]]

    virtual void
    setDeferred( std::string_view deferred, bool update );

    [[maybe_unused]]
    virtual void
    setDue( time_point_t tp, bool update );

    [[maybe_unused]]
    virtual void
    setDue( std::string_view due_str, bool update );

    [[maybe_unused]]
    virtual void
    setTaskType( const std::string& taskType, bool update );

    [[maybe_unused]]
    virtual void
    setIsRepeating( int isRepeating, bool update );

    [[maybe_unused]]
    virtual void
    setFlagged( int flagged, bool update );

    [[maybe_unused]]
    virtual void
    setFlagged( bool flagged, bool update );

    [[maybe_unused]]
    virtual void
    setRepeatFrom( RepeatFrom repeatFrom, bool update );

    [[maybe_unused]]
    virtual void
    setRepeatFrom( std::string_view rptFromStr, bool update );

    [[maybe_unused]]
    virtual void
    setRepeatSchedule( std::string_view schedule, bool update );
};
} // namespace gtd

std::ostream&
operator<<( std::ostream& out, const gtd::Completable& completable );

#endif //  COMPLETABLE_HPP_
