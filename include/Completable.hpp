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
private:
	// Hide from inheriting classes
	using pContainer = std::shared_ptr<GtdContainer<Completable>>;
	pContainer				        _gtdItems {nullptr};

protected:
    std::optional<unique_id_t>		_o_contextId{std::nullopt};
    std::optional<time_point_t> 	_o_deferred{std::nullopt};
    std::optional<time_point_t> 	_o_due{std::nullopt};
    bool                        	_isRepeating{false};
    bool                        	_flagged{false};
    RepeatFrom                  	_repeatFrom{RepeatFrom::Due};
    std::string_view            	_repeatSchedule{"30 16 * * *"}; // Every day at 4:30pm

public:
    // CTORS
	/*************************************************************************/
    explicit
    Completable( std::string_view name = "" );
	Completable( const Completable& );
	Completable( Completable&& );

    ~Completable() override = default;

	// ASSIGMENT OPERATORS
	/*************************************************************************/
	Completable&
	operator=( const Completable& );
	Completable&
	operator=( Completable&& );

    // GETTERS
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
    void
    setContextId( unique_id_t contextId, bool update = true );

    void
    setDeferred( time_point_t deferred, bool update = true );
    [[maybe_unused]]

    void
    setDeferred( std::string_view deferred, bool update = true );

    [[maybe_unused]]
    void
    setDue( time_point_t tp, bool update = true );

    [[maybe_unused]]
    void
    setDue( std::string_view due_str, bool update = true );

    [[maybe_unused]]
    void
    setTaskType( const std::string& taskType, bool update = true );

    [[maybe_unused]]
    void
    setIsRepeating( int isRepeating, bool update = true );

    [[maybe_unused]]
    void
    setFlagged( int flagged, bool update = true );

    [[maybe_unused]]
    void
    setRepeatFrom( RepeatFrom repeatFrom, bool update = true );

    [[maybe_unused]]
    void
    setRepeatFrom( std::string_view rptFromStr, bool update = true );

    [[maybe_unused]]
    void
    setRepeatSchedule( std::string_view schedule, bool update = true );
};
} // namespace gtd

std::ostream&
operator<<( std::ostream& out, const gtd::Completable& completable );

#endif //  COMPLETABLE_HPP_
