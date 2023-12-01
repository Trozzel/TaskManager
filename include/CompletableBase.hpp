//
// Created by George Ford on 1/28/22.
//

#ifndef __COMPLETABLE_BASE_HPP__
#define  __COMPLETABLE_BASE_HPP__

#include <iostream>
#include <string>
#include <filesystem>
#include <string_view>
#include <type_traits>

#include "GtdBase.hpp"
#include "GtdHelper.hpp"

namespace gtd {

/// \param _contextId - uniqueId of the context to which task is assigned
/// \param _projectId - uniqueId of the project to which the task belongs
/// \param _notes - notes
/// \param _deferred - deferred start date 
/// \param _due - due date 
/// \param _isRepeating - if this is a recurring task
/// \param _flagged - is flagged or not
/// \param _repeatSchedule - crontab format repeat schedule
class CompletableBase : public GtdBase {
protected:
    LL_t                _contextId {-1};
    std::string         _notes {};
    time_point_t        _deferred {std::chrono::system_clock::now()};
    time_point_t        _due {std::chrono::system_clock::now()};
    bool                _isRepeating {false};
	bool				_flagged {false};
	RepeatFrom			_repeatFrom { RepeatFrom::Due };
	std::string_view	_repeatSchedule {"30 16 * * *"}; // Every day at 4:30pm

public:
    // CTORS
    CompletableBase(std::string_view name = "") :
            GtdBase(name) {
    }

	/// \brief although pure virtual destructor, still needs definition for
	/// children destructors
    virtual ~CompletableBase() = 0;

    // GETTERS
    [[nodiscard]] [[maybe_unused]]
	constexpr LL_t
    contextId() const noexcept {
        return _contextId;
    }

    [[nodiscard]] [[maybe_unused]]
	std::string_view 
    notes() const;

    [[nodiscard]] [[maybe_unused]]
	constexpr const time_point_t
    deferred() const noexcept {
        return _deferred;
    }

    [[nodiscard]]
	constexpr time_point_t  
    due() const noexcept {
        return _due;
    }

    [[nodiscard]] [[maybe_unused]]
	constexpr bool 
    isRepeating() const noexcept {
        return _isRepeating;
    }

    [[nodiscard]] [[maybe_unused]]
	constexpr bool
    flagged() const noexcept {
		return _flagged;
	}

	constexpr RepeatFrom
	repeatFrom() const noexcept {
		return _repeatFrom;
	}

	[[nodiscard]]
	constexpr std::string_view
	repeatSchedule() const noexcept {
		return _repeatSchedule; 
	}

    // SETTERS
    /*************************************************************************/
    [[maybe_unused]]
	constexpr void 
    setContextId(LL_t contextId) noexcept {
        _contextId = contextId;
    }

	void 
    setContextIdFromStr(const std::string& contextIdStr) {
        _contextId = (contextIdStr.empty()) ? -1 : stoll(contextIdStr);
    }

    [[maybe_unused]]
    void setNotes(std::string_view notes) {
        _notes = notes;
    }

	constexpr void 
    setDeferred(time_point_t deferred) {
        _deferred = deferred;
    }

	[[maybe_unused]]
	void 
    setDeferred(std::string_view deferredStr);

	[[maybe_unused]]
	constexpr void 
    setDue(time_point_t due) {
		_due = due;
	}

	[[maybe_unused]]
	void 
    setDue(std::string_view dueStr);


	[[maybe_unused]]
	void 
    setTaskType(const std::string &taskType);

	[[maybe_unused]]
	constexpr void 
    setIsRepeating(const int isRepeating) noexcept {
		_isRepeating = isRepeating;
	}

    [[maybe_unused]]
	constexpr void
    setFlagged(const int flagged) noexcept {
		_flagged = flagged;
	}

    [[maybe_unused]]
	constexpr void
    setRepeatFrom(RepeatFrom repeatFrom) noexcept;

	[[maybe_unused]]
	void
	setRepeatFrom(std::string_view repeatFromStr);

    [[maybe_unused]]
	constexpr void
	setRepeatSchedule(std::string_view repeatSchedule) noexcept {
		_repeatSchedule = repeatSchedule;
	}
};

} // namespace gtd

std::ostream&
operator<<(std::ostream &out, const gtd::CompletableBase& completable);

#endif //  __COMPLETABLE_BASE_HPP__
