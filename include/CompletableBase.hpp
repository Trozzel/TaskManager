//
// Created by George Ford on 1/28/22.
//

#ifndef __COMPLETABLE_BASE_HPP__
#define  __COMPLETABLE_BASE_HPP__

#include <iostream>
#include <optional>
#include <string>
#include <filesystem>
#include <string_view>
#include <type_traits>

#include "GtdBase.hpp"
#include "GtdHelper.hpp"

namespace gtd {

/// \param _contextId - uniqueId of the context to which task is assigned
/// \param _projectId - uniqueId of the project to which the task belongs
/// \param _deferred - deferred start date 
/// \param _due - due date 
/// \param _isRepeating - if this is a recurring task
/// \param _flagged - is flagged or not
/// \param _repeatSchedule - crontab format repeat schedule
class CompletableBase : public GtdBase {
protected:
	std::optional<unique_id_t>		_o_contextId {std::nullopt};
	std::optional<time_point_t>     _o_deferred {std::nullopt};
    std::optional<time_point_t>     _o_due {std::nullopt};
    bool							_isRepeating {false};
	bool							_flagged {false};
	RepeatFrom						_repeatFrom { RepeatFrom::Due };
	std::string_view				_repeatSchedule {"30 16 * * *"}; // Every day at 4:30pm

public:
    // CTORS
    CompletableBase(USMgr&, std::string_view name = "");

	/// \brief although pure virtual destructor, still needs definition for
	/// children destructors
    virtual ~CompletableBase() = 0;

    // GETTERS
	/*************************************************************************/
    [[nodiscard]] [[maybe_unused]]
	constexpr std::optional<unique_id_t>
    contextId() const noexcept {
        return _o_contextId;
    }

    [[nodiscard]] [[maybe_unused]]
	constexpr const std::optional<time_point_t>
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

	[[nodiscard]]
	constexpr RepeatFrom
	repeatFrom() const noexcept {
		return _repeatFrom;
	}

	[[nodiscard]]
	std::string_view
	repeatFromStr() const;

	[[nodiscard]]
	constexpr std::string_view
	repeatSchedule() const noexcept {
		return _repeatSchedule; 
	}

    // SETTERS
    /*************************************************************************/
    [[maybe_unused]]
	void 
    setContextId(unique_id_t contextId, bool update); 

	void 
    setDeferred(time_point_t deferred, bool update); 
	[[maybe_unused]]

	void 
    setDeferred(std::string_view deferredStr, bool update);

	[[maybe_unused]]
	void 
    setDue(time_point_t due, bool update); 

	[[maybe_unused]]
	void 
    setDue(std::string_view dueStr, bool update);

	[[maybe_unused]]
	void 
    setTaskType(const std::string &taskType, bool update);

	[[maybe_unused]]
	void 
    setIsRepeating(const int isRepeating, bool update); 

    [[maybe_unused]]
	void
    setFlagged(const int flagged, bool update); 

    [[maybe_unused]]
	void
    setRepeatFrom(RepeatFrom repeatFrom, bool update);

	[[maybe_unused]]
	void
	setRepeatFrom(std::string_view repeatFromStr, bool update);

    [[maybe_unused]]
	void
	setRepeatSchedule(std::string_view repeatSchedule, bool update) ;
};

} // namespace gtd

std::ostream&
operator<<(std::ostream &out, const gtd::CompletableBase& completable);

#endif //  __COMPLETABLE_BASE_HPP__
