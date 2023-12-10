//
// Created by George Ford on 1/28/22.
//
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <system_error>

#include "CompletableBase.hpp"
#include "GtdBase.hpp"
#include "GtdHelper.hpp"

namespace gtd {

// CTORS
/*****************************************************************************/
CompletableBase::CompletableBase(USMgr& updateStackMgr, std::string_view name) :
	GtdBase(updateStackMgr, name) {}

// MUST DEFINE PURE VIRTUAL DESTRUCTOR
CompletableBase::~CompletableBase() = default;

// GETTERS
/*****************************************************************************/
std::optional<std::string>
CompletableBase::deferredStr() const {
	if(_o_deferred) {
		return timePointToStr(*_o_deferred);
	}
	return std::nullopt;
}

std::optional<std::string>
CompletableBase::dueStr() const {
	if(_o_due) {
		return timePointToStr(*_o_due);
	}
	return std::nullopt;
}

std::string_view
CompletableBase::repeatFromStr() const {
	return repeatFromToStr(_repeatFrom);
}

// SETTERS
/*****************************************************************************/
void 
CompletableBase::setContextId(unique_id_t contextId, bool update) {
	_o_contextId = contextId;
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "contextId");
	}
}

void 
CompletableBase::setDeferred(time_point_t deferred, bool update) {
	_o_deferred = deferred;
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "deferred");
	}
}

void 
CompletableBase::setDeferred(std::string_view deferredStr, bool update) {
    _o_deferred = strToTimePoint(deferredStr);
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "deferred");
	}
}

void 
CompletableBase::setDue(time_point_t due, bool update) {
	_o_due = due;
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "due");
	}
}

void
CompletableBase::setDue(std::string_view dueStr, bool update) {
    _o_due = strToTimePoint(dueStr);
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "due");
	}
}

void 
CompletableBase::setIsRepeating(const int isRepeating, bool update) {
	_isRepeating = isRepeating;
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "isRepeating");
	}
}

void
CompletableBase::setFlagged(const int flagged, bool update) {
	_flagged = flagged;
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "flagged");
	}
}

void
CompletableBase::setRepeatSchedule(std::string_view repeatSchedule, bool update) {
	_repeatSchedule = repeatSchedule;
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "repeatSchedule");
	}
}

void
CompletableBase::setRepeatFrom(std::string_view repeatFromStr, bool update) {
	_repeatFrom = strToRepeatFrom(repeatFromStr);
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "repeatFrom");
	}
}

std::ostream&
operator<<(std::ostream& out, const CompletableBase& task) {
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
