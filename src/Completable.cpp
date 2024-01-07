//
// Created by George Ford on 1/28/22.
//
#include "Completable.hpp"
#include "GtdContainer.hpp"
#include "UpdateStack.hpp"

namespace gtd {
// CTORS
/*****************************************************************************/
Completable::Completable( const std::string_view name ) :
    GtdBase(name)
{}

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
	if constexpr (gtd_category::constructible && gtd_category::completable) {
		_o_deferred = deferred;
		if ( update ) {
			auto& us = _gtdItems->updateStack();
			if(this->uniqueId()) {
				us.push(*this->uniqueId(), "deferred", *deferredStr());
			}
		}
	}
	else {
		std::cerr << "'*this' must gtd_category::constructible == true\n";
		std::cerr << "'*this' must gtd_category::completable == true\n";
	}
}

void
Completable::setDeferred( const std::string_view deferred, bool update ) {
	if constexpr (gtd_category::constructible && gtd_category::completable) {
		_o_deferred = strToTimePoint(deferred);
		if ( update ) {
			auto& us = _gtdItems->updateStack();
			if(this->uniqueId()) {
				us.push(*this->uniqueId(), "deferred", *deferredStr());
			}
		}
	}
	else {
		std::cerr << "'*this' must gtd_category::constructible == true\n";
		std::cerr << "'*this' must gtd_category::completable == true\n";
	}
}

void
Completable::setDue( const time_point_t tp, bool update ) {
	if constexpr (gtd_category::constructible && gtd_category::completable) {
		_o_due = tp;
		if ( update ) {
			auto& us = _gtdItems->updateStack();
			if(this->uniqueId()) {
				us.push(*this->uniqueId(), "due", *dueStr());
			}
		}
	}
	else {
		std::cerr << "'*this' must gtd_category::constructible == true\n";
		std::cerr << "'*this' must gtd_category::completable == true\n";
	}
}

void
Completable::setDue( const std::string_view due_str, const bool update ) {
	if constexpr (gtd_category::constructible && gtd_category::completable) {
		_o_due = strToTimePoint(due_str);
		if ( update ) {
			auto& us = _gtdItems->updateStack();
			if(this->uniqueId()) {
				us.push(*this->uniqueId(), "due", *dueStr());
			}
		}
	}
	else {
		std::cerr << "'*this' must gtd_category::constructible == true\n";
		std::cerr << "'*this' must gtd_category::completable == true\n";
	}
}

void
Completable::setIsRepeating( const int isRepeating, const bool update ) {
	if constexpr (gtd_category::constructible && gtd_category::completable) {
		_isRepeating = static_cast<bool>(isRepeating);
		if ( update ) {
			auto& us = _gtdItems->updateStack();
			if(this->uniqueId()) {
				us.push(*this->uniqueId(), "isRepeating", this->isRepeating());
			}
		}
	}
	else {
		std::cerr << "'*this' must gtd_category::constructible == true\n";
		std::cerr << "'*this' must gtd_category::completable == true\n";
	}
}

void
Completable::setFlagged( const int flagged, const bool update ) {
	if constexpr (gtd_category::constructible && gtd_category::completable) {
		_flagged = static_cast<bool>(flagged);
		if ( update ) {
			auto& us = _gtdItems->updateStack();
			if(this->uniqueId()) {
				us.push(*this->uniqueId(), "flagged", this->flagged());
			}
		}
	}
	else {
		std::cerr << "'*this' must gtd_category::constructible == true\n";
		std::cerr << "'*this' must gtd_category::completable == true\n";
	}
}

void
Completable::setRepeatSchedule( std::string_view schedule, bool update ) {
	if constexpr (gtd_category::constructible && gtd_category::completable) {
		_repeatSchedule = schedule;
		if ( update ) {
			auto& us = _gtdItems->updateStack();
			if(this->uniqueId()) {
				us.push(*this->uniqueId(), "repeatSchedule", repeatSchedule());
			}
		}
	}
	else {
		std::cerr << "'*this' must gtd_category::constructible == true\n";
		std::cerr << "'*this' must gtd_category::completable == true\n";
	}
}

void
Completable::setRepeatFrom( std::string_view rptFromStr, bool update ) {
	if constexpr (gtd_category::constructible && gtd_category::completable) {
		_repeatFrom = strToRepeatFrom(rptFromStr);
		if ( update ) {
			auto& us = _gtdItems->updateStack();
			if(this->uniqueId()) {
				us.push(*this->uniqueId(), "repeatFrom", repeatFromStr());
			}
		}
	}
	else {
		std::cerr << "'*this' must gtd_category::constructible == true\n";
		std::cerr << "'*this' must gtd_category::completable == true\n";
	}
}

} // namespace gtd
