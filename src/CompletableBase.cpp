//
// Created by George Ford on 1/28/22.
//
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <system_error>

#include "CompletableBase.hpp"

using namespace std;

namespace gtd {

// MUST DEFINE PURE VIRTUAL DESTRUCTOR
CompletableBase::~CompletableBase() = default;

// GETTERS
/*****************************************************************************/
std::string_view
CompletableBase::notes() const {
    return std::string_view(_notes);
}

// SETTERS
/*****************************************************************************/
void 
CompletableBase::setDeferred(std::string_view deferredStr) {
    _deferred = strToTimePoint(deferredStr);
}

void
CompletableBase::setDue(std::string_view dueStr) {
    _due = strToTimePoint(dueStr);
}

void
CompletableBase::setRepeatFrom(std::string_view repeatFromStr) {
	_repeatFrom = strToRepeatFrom(repeatFromStr);
}


std::ostream& 
operator<<(std::ostream& out, const CompletableBase& task) {
    // SEND BASE TO STREAM
    const auto* pBase = static_cast<const GtdBase*>(&task);
    out << *pBase;

    // SEND REMAINED TO STREAM
    out << task.notes() << " " << timePointToStr(task.deferred()) << " "
        << timePointToStr(task.due()) << " "
        << ios::boolalpha << task.isRepeating(); 

    return out;
}

} // namespace gtd
