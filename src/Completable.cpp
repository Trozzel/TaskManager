//
// Created by George Ford on 1/28/22.
//
#include <chrono>

#include "Completable.hpp"
#include "GtdBase.hpp"
#include "GtdHelper.hpp"
#include "UpdateStack.hpp"

namespace gtd {
// CTORS
/*****************************************************************************/
Completable::Completable( CompleteableContainer& gtdItems, std::string_view name ) :
    GtdBase(gtdItems, name),
    _gtdItems(gtdItems)
{}

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
Completable::setContextId( unique_id_t contextId, bool update ) {
    *_o_contextId = contextId;
    if ( update ) {
        auto& usm = _gtdItems.updateStackManager();
        auto& pUpdateStack = usm.getUpdateStack();
        if(this->uniqueId()) {
            pUpdateStack->push(*this->uniqueId(), "contextId", contextId());
        }
    }
}

void
Completable::setDeferred( time_point_t deferred, bool update ) {
    _o_deferred = deferred;
    if ( update ) {
        auto& usm = _gtdItems.updateStackManager();
        auto& pUpdateStack = usm.getUpdateStack();
        if(this->uniqueId()) {
            pUpdateStack->push(*this->uniqueId(), "deferred", *deferredStr());
        }
    }
}

void
Completable::setDeferred( std::string_view deferred, bool update ) {
    _o_deferred = strToTimePoint(deferred);
    if ( update ) {
        auto& usm = _gtdItems.updateStackManager();
        auto& pUpdateStack = usm.getUpdateStack();
        if(this->uniqueId()) {
            pUpdateStack->push(*this->uniqueId(), "deferred", *deferredStr());
        }
    }
}

void
Completable::setDue( time_point_t tp, bool update ) {
    _o_due = tp;
    if ( update ) {
        auto& usm = _gtdItems.updateStackManager();
        auto& pUpdateStack = usm.getUpdateStack();
        if(this->uniqueId()) {
            pUpdateStack->push(*this->uniqueId(), "due", *dueStr());
        }
    }
}

void
Completable::setDue( std::string_view due_str, bool update ) {
    _o_due = strToTimePoint(due_str);
    if ( update ) {
        auto& usm = _gtdItems.updateStackManager();
        auto& pUpdateStack = usm.getUpdateStack();
        if(this->uniqueId()) {
            pUpdateStack->push(*this->uniqueId(), "due", *dueStr());
        }
    }
}

void
Completable::setIsRepeating( const int isRepeating, bool update ) {
    _isRepeating = static_cast<bool>(isRepeating);
    if ( update ) {
        auto& usm = _gtdItems.updateStackManager();
        auto& pUpdateStack = usm.getUpdateStack();
        if(this->uniqueId()) {
            pUpdateStack->push(*this->uniqueId(), "isRepeating", isRepeating());
        }
    }
}

void
Completable::setFlagged( const int flagged, bool update ) {
    _flagged = static_cast<bool>(flagged);
    if ( update ) {
        auto& usm = _gtdItems.updateStackManager();
        auto& pUpdateStack = usm.getUpdateStack();
        if(this->uniqueId()) {
            pUpdateStack->push(*this->uniqueId(), "flagged", flagged());
        }
    }
}

void
Completable::setRepeatSchedule( std::string_view schedule, bool update ) {
    _repeatSchedule = schedule;
    if ( update ) {
        auto& usm = _gtdItems.updateStackManager();
        auto& pUpdateStack = usm.getUpdateStack();
        if(this->uniqueId()) {
            pUpdateStack->push(*this->uniqueId(), "repeatSchedule", repeatSchedule());
        }
    }
}

void
Completable::setRepeatFrom( std::string_view rptFromStr, bool update ) {
    _repeatFrom = strToRepeatFrom(rptFromStr);
    if ( update ) {
        auto& usm = _gtdItems.updateStackManager();
        auto& pUpdateStack = usm.getUpdateStack();
        if(this->uniqueId()) {
            pUpdateStack->push(*this->uniqueId(), "repeatFrom", repeatFromStr());
        }
    }
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
