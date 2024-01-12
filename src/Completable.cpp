//
// Created by George Ford on 1/28/22.
//
#include "Completable.hpp"
#include "GtdBase.hpp"
#include "GtdContainer.hpp"

namespace gtd {
// CTORS
/*****************************************************************************/
Completable::Completable( const std::string_view name ) :
    GtdBase(name) {}

Completable::Completable( Completable&& other ) noexcept :
    GtdBase(std::move(other)),
    _o_contextId(other._o_contextId),
    _o_deferred(other._o_deferred),
    _o_due(other._o_due),
    _isRepeating(other._isRepeating),
    _flagged(other._flagged),
    _repeatFrom(other._repeatFrom),
    _repeatSchedule(other._repeatSchedule) {}

// DTOR
Completable::~Completable() = default;

// ASSIGMENT OPERATORS
/*****************************************************************************/
Completable&
Completable::operator=( Completable&& other ) noexcept {
    if ( &other != this ) {
        GtdBase::operator=(std::move(other));
        _o_contextId    = other._o_contextId;
        _o_deferred     = other._o_deferred;
        _o_due          = other._o_due;
        _isRepeating    = other._isRepeating;
        _flagged        = other._flagged;
        _repeatFrom     = other._repeatFrom;
        _repeatSchedule = other._repeatSchedule;
    }
    return *this;
}

bool
Completable::operator==( const Completable& other ) const {
    return GtdBase::operator==(other) &&
            _o_contextId == other._o_contextId &&
            _o_deferred == other._o_deferred &&
            _o_due == other._o_due &&
            _isRepeating == other._isRepeating &&
            _flagged == other._flagged &&
            _repeatFrom == other._repeatFrom &&
            _repeatSchedule == other._repeatSchedule;
}

bool
Completable::operator!=( const Completable& other ) const {
    return !operator==(other);
}

void
Completable::setContextId( unique_id_t contextId, bool update ) {}

void
Completable::setTaskType( const std::string& taskType, bool update ) {}

void
Completable::setRepeatFrom( RepeatFrom repeatFrom, bool update ) {}

// GETTERS
/*****************************************************************************/
std::optional<std::string>
Completable::deferredStr() const {
    if ( _o_deferred ) {
        return timePointToStr(*_o_deferred);
    }
    return std::nullopt;
}

std::optional<std::string>
Completable::dueStr() const {
    if ( _o_due ) {
        return timePointToStr(*_o_due);
    }
    return std::nullopt;
}

// SETTERS
/*****************************************************************************/
void
Completable::setDeferred( const time_point_t deferred, bool update ) {
    _o_deferred = deferred;
}

void
Completable::setDeferred( const std::string_view deferred, bool update ) {
    _o_deferred = strToTimePoint(deferred);
}

void
Completable::setDue( const time_point_t tp, bool update ) {
    _o_due = tp;
}

void
Completable::setDue( const std::string_view due_str, const bool update ) {
    _o_due = strToTimePoint(due_str);
}

void
Completable::setIsRepeating( const int isRepeating, const bool update ) {
    _isRepeating = static_cast<bool>(isRepeating);
}

void
Completable::setFlagged( const int flagged, const bool update ) {
    _flagged = static_cast<bool>(flagged);
}

void
Completable::setFlagged( const bool flagged, const bool update ) {
    _flagged = flagged;
}

void
Completable::setRepeatSchedule( std::string_view schedule, bool update ) {
    _repeatSchedule = schedule;
}

void
Completable::setRepeatFrom( std::string_view rptFromStr, bool update ) {
    _repeatFrom = strToRepeatFrom(rptFromStr);
}
} // namespace gtd
