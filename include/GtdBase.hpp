#ifndef __GTDBASE_HPP__
#define __GTDBASE_HPP__

#include <cstring>
#include <exception>
#include <sstream>
#include <iomanip>
#include <memory>
#include <string>
#include <string_view>
#include <chrono>
#include <cctype>
#include <utility>

#include <fmt/chrono.h>

#include "GtdHelper.hpp"

using LL_t = long long;

namespace gtd {

class GtdBase {

protected:
    LL_t         _uniqueId{-1};
    std::string  _name;
    Status       _status{Status::Active};
    time_point_t _created;
    time_point_t _modified;
    LL_t         _parentId{-1};    // _parentId == -1 --> no parent

public:
    // CTORS
    /**************************************************************************/
    GtdBase() = default;

    GtdBase(std::string_view name) :
            _uniqueId(-1),
            _name(name),
            _status(Status::Active),
            _created(std::chrono::system_clock::now()),  // trivially_copyable
            _modified(std::chrono::system_clock::now()), // trivially_copyable
            _parentId(-1) {}

    // BY READING IN DATA AS STRINGS
    GtdBase(const std::string &uniqueIdStr,
            std::string_view name,
            const std::string &statusStr,
            const std::string &createdStr = "",
            const std::string &modifiedStr = "",
            const std::string &parentIdStr = "") :
            _uniqueId(stoll(uniqueIdStr)),
            _name(name),
            _status(strToStatus(statusStr)),
            _parentId(stoll(parentIdStr))
	{
        // IF CREATED STRING IS EMPTY -> ::now()
        if (createdStr.empty()) {
            _created = std::chrono::system_clock::now();
        }
        else {
            _created = strToTimePoint(createdStr);
        }
        // IF MODIFIED STRING IS EMPTY -> ::now()
        if (modifiedStr.empty()) {
            _modified = std::chrono::system_clock::now();
        }
        else {
            _modified = strToTimePoint(modifiedStr);
        }
    }

	/// \brief declared as a virtual destructor. But since children will call
	/// this destructor, it is 
    virtual ~GtdBase() = 0; // pure virtual destructor

    // GETTERS
    /**************************************************************************/
    [[nodiscard]]
    constexpr LL_t 
	uniqueId() const noexcept { return _uniqueId; }

    constexpr std::string_view 
	name() const noexcept { return _name;} const // implicit conversion to std::string_view

    constexpr Status 
	status() const noexcept { return _status; }

    constexpr std::string_view 
	statusStr() const noexcept { return statusToStr(_status); }

    constexpr time_point_t 
	created() const noexcept { return _created; }

    std::string createdStr() 
	const { return fmt::format("{}", _created); }

    constexpr time_point_t 
	modified() const noexcept { return _modified; }

    std::string 
	modifiedStr() const { return fmt::format("{}", _modified); }

    constexpr LL_t parentId() const noexcept { return _parentId; } const

    // SETTERS
    /**************************************************************************/
    void 
	setUniqueIdFromStr(const std::string &uniqueIdStr) {
        _uniqueId = (uniqueIdStr.empty()) ? -1 : stoll(uniqueIdStr);
    }

    [[maybe_unused]]
    void 
	setUniqueId(LL_t id) noexcept {
        _uniqueId = id;
    }

    void 
	setName(std::string_view name) noexcept {
        _name = name;
    }

    void 
	setStatus(std::string_view statusStr) {
        _status = strToStatus(statusStr);
    }

    [[maybe_unused]]
    constexpr void 
	setStatus(Status status) noexcept {
        _status = status;
    }

    void 
	setCreated(std::string_view created) {
        _created = strToTimePoint(created);
    }

    [[maybe_unused]]
    constexpr void 
	setCreated(time_point_t tp) noexcept {
        _created = tp;
    }

    void 
	setModified(std::string_view modified) {
        _modified = strToTimePoint(modified);
    }

    [[maybe_unused]]
    constexpr void 
	setModified(time_point_t tp) noexcept {
        _modified = tp;
    }

    virtual void 
	setParentIdFromStr(const std::string &parentIdStr) {
        _parentId = (parentIdStr.empty()) ? -1 : stoll(parentIdStr);
    }

    [[maybe_unused]]
    constexpr virtual void 
	setParentId(LL_t id) {
        _parentId = id;
    }

    friend std::ostream&
	operator<<(std::ostream &out, const GtdBase &base) {
        out << base._uniqueId << " " << base._name << " "
            << statusToStr(base._status) << " "
            << timePointToStr(base._created) << " "
            << timePointToStr(base._modified) << " "
            << base._parentId;

        return out;
    };

};
//								HELPER FUNCTIONS
/*****************************************************************************/

/// \brief Get parent from task
/// \note Must check for it == gtdItems.end() on call
template<typename Gtd, typename VectorGtd>
const auto
getParent_it(Gtd& child, VectorGtd& gtdItems) {
    static_assert(std::is_base_of_v<gtd::GtdBase, Gtd>);
	static_assert(std::is_base_of_v<gtd::GtdBase, typename VectorGtd::value_type>);
    auto parentId = child.parentId();
    auto it = std::find_if(gtdItems.begin(), gtdItems.end(), 
			[parentId](const Gtd& item) { 
			return item.uniqueId() == parentId;
    });
    return it;
}

/// Find element by uniqueId
template<typename Gtd>
std::string_view 
getNameById(const std::vector<const Gtd>& gtdItems, LL_t id) {
	static_assert(std::is_base_of_v<gtd::GtdBase, Gtd>);
	auto it = std::find_if(gtdItems.begin(), gtdItems.end(),
                            [&gtdItems, id](const Gtd& task) {
                                return task.uniqueId() == id;
                            });
    return (it != gtdItems.end()) ? it->name() : "NA";
}

} // namespace gtd

#endif // __GTDBASE_HPP__
