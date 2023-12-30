//
// Created by George Ford on 1/28/22.
//
#include <chrono>

#include "Completable.hpp"
#include "GtdBase.hpp"
#include "GtdHelper.hpp"

namespace gtd {
// CTORS
/*****************************************************************************/
Completable::Completable( CompleteableContainer& gtdItems, std::string_view name ) :
    GtdBase(gtdItems, name),
    _gtdItems(gtdItems) {}

// MUST DEFINE PURE VIRTUAL DESTRUCTOR
Completable::~Completable() = default;

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

std::string_view
Completable::repeatFromStr() const {
    return repeatFromToStr(_repeatFrom);
}

// SETTERS
/*****************************************************************************/
void
Completable::setContextId( const unique_id_t id, bool update ) {
    *_o_contextId = id;
    pushToUpdateStack("id", contextId(), update);
}

void
Completable::setDeferred( time_point_t deferred, bool update ) {
    _o_deferred = deferred;
    pushToUpdateStack("deferred", deferredStr(), update);
}

void
Completable::setDeferred( std::string_view deferred, bool update ) {
    _o_deferred = strToTimePoint(deferred);
    pushToUpdateStack("deferred", deferredStr(), update);
}

void
Completable::setDue( time_point_t tp, bool update ) {
    _o_due = tp;
    pushToUpdateStack("due", dueStr(), update);
}

void
Completable::setDue( std::string_view due_str, bool update ) {
    _o_due = strToTimePoint(due_str);
    pushToUpdateStack("due", dueStr(), update);
}

void
Completable::setIsRepeating( const int is_repeating, bool update ) {
    _isRepeating = static_cast<bool>(is_repeating);
    pushToUpdateStack("isRepeating", isRepeating(), update);
}

void
Completable::setFlagged( const int flagged, bool update ) {
    _flagged = static_cast<bool>(flagged);
    pushToUpdateStack("flagged", this->flagged(), update);
}

void
Completable::setRepeatSchedule( std::string_view schedule, bool update ) {
    _repeatSchedule = schedule;
    pushToUpdateStack("repeatSchedule", repeatSchedule(), update);
}

void
Completable::setRepeatFrom( std::string_view rptFromStr, bool update ) {
    _repeatFrom = strToRepeatFrom(rptFromStr);
    pushToUpdateStack("repeatFrom", repeatFromStr(), update);
}

std::ostream&
operator<<( std::ostream& out, const Completable& task ) {
    // SEND BASE TO STREAM
    const auto* pBase = static_cast<const GtdBase*>(&task);
    out << *pBase;

    // SEND REMAINED TO STREAM
    out << *task.notes() << " "
            << *task.deferredStr() << " "
            << *task.dueStr() << " "
            << std::ios::boolalpha << task.isRepeating();

    return out;
}
} // namespace gtd
