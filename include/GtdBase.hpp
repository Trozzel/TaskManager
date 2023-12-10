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
#include <stack>

#include <fmt/chrono.h>

#include "GtdHelper.hpp"

using update_pair_t = std::pair<unique_id_t, std::string_view>;

namespace gtd {
class USMgr;

class GtdBase {

protected:
	std::optional<unique_id_t>				 _o_uniqueId{ std::nullopt };
    std::string  							 _name;
    Status       							 _status{Status::Active};
    time_point_t 							 _created;
    time_point_t 							 _modified;
	std::optional<unique_id_t> 				 _o_parentId{ std::nullopt };
	std::optional<std::string>  			 _o_notes { std::nullopt };
	USMgr&									 _updateStackMgr;

public:
    // CTORS
    /**************************************************************************/
	GtdBase(USMgr&, std::string_view name = "");

	/// \brief declared as a virtual destructor. But since children will call
	/// this destructor, it is defined in GtdBase.cpp
    virtual ~GtdBase() = 0; // pure virtual destructor

    // GETTERS
    /**************************************************************************/
    [[nodiscard]]
    std::optional<unique_id_t>
	uniqueId() const noexcept { return _o_uniqueId; }

    [[nodiscard]]
    constexpr std::string_view 
	name() const noexcept { return _name;} // implicit conversion to std::string_view

    [[nodiscard]]
    constexpr Status 
	status() const noexcept { return _status; }

    [[nodiscard]]
    constexpr std::string_view 
	statusStr() const noexcept { return statusToStr(_status); }

    [[nodiscard]]
    constexpr time_point_t 
	created() const noexcept { return _created; }

    [[nodiscard]]
    std::string createdStr() 
	const { return fmt::format("{}", _created); }

    [[nodiscard]]
    constexpr time_point_t 
	modified() const noexcept { return _modified; }

    [[nodiscard]]
    std::string 
	modifiedStr() const { return fmt::format("{}", _modified); }

    [[nodiscard]]
    std::optional<unique_id_t>
	parentId() const noexcept { return _o_parentId; }

    [[nodiscard]]
	std::optional<std::string_view>
	notes() const;

    // SETTERS
    /**************************************************************************/
    [[maybe_unused]]
    void 
	setUniqueId(unique_id_t id) noexcept {
        _o_uniqueId = id;
    }

    virtual void 
	setName(std::string_view name, bool update);

    virtual void 
	setStatus(std::string_view statusStr, bool update);

    [[maybe_unused]]
    virtual void 
	setStatus(Status status, bool update) noexcept;

    virtual void 
	setCreated(std::string_view created, bool);

    [[maybe_unused]]
    virtual void 
	setCreated(time_point_t tp, bool update) noexcept;

    virtual void 
	setModified(std::string_view modified, bool update);

    [[maybe_unused]]
    virtual void 
	setModified(time_point_t tp, bool update) noexcept;

    [[maybe_unused]]
    virtual void 
	setParentId(unique_id_t id, bool update);

	[[maybe_unused]]
	virtual void
	setNotes(std::string_view notes, bool update);


};
//								HELPER FUNCTIONS
/*****************************************************************************/

/// \brief Get parent from task
/// \note Must check for it == gtdItems.end() on call
template<typename Gtd, typename VectorGtd>
auto
getParent_it(Gtd& child, VectorGtd& gtdItems) {
    static_assert(std::is_base_of_v<gtd::GtdBase, Gtd>);
	static_assert(std::is_base_of_v<gtd::GtdBase, typename VectorGtd::value_type>);
    auto parentId = *child.parentId();
    auto it = std::find_if(gtdItems.begin(), gtdItems.end(), 
			[parentId](const Gtd& item) -> bool { 
			if(!item.parentId()) {
				return false;
			}
			return *item.uniqueId() == parentId;
    });
    return it;
}

/// Find element by uniqueId
template<typename Gtd>
std::optional<std::string_view>
getNameById(const std::vector<const Gtd>& gtdItems, unique_id_t id) {
	static_assert(std::is_base_of_v<gtd::GtdBase, Gtd>);
	auto it = std::find_if(gtdItems.begin(), gtdItems.end(),
                            [&gtdItems, id](const Gtd& task) {
								if(!task.uniqueId()) {
									return false;
								}
                                return task.uniqueId() == id;
                            });
    return (it != gtdItems.end()) ? it->name() : std::nullopt;
}

std::ostream&
operator<<(std::ostream &out, const GtdBase &base); 


//							UPDATE STACK BEGIN
/*****************************************************************************/

// CLASS UPDATE STACK
/*****************************************************************************/
class UpdateStack {
private:
	std::string_view          _tableName;
	std::stack<update_pair_t> _dbUpdateStack;

public:
    UpdateStack(std::string_view table);

    void
    clear();

    void
    push(const GtdBase &gtdItem, std::string_view colName);

    void
    pop();

    update_pair_t &
    top();

    std::string
    compose();
}; // class UpdateStack

// CLASS UpdateStackManager
/*****************************************************************************/
class USMgr {
	// unique_ptr deleter that returns resource to the UpdateStackMgr object
    struct USPtrDeleter {
        USMgr& _usMgr;
        explicit USPtrDeleter(USMgr& usm);
        void operator()(UpdateStack* updateStackPtr);
	};

private:
    using USPtr_t = std::unique_ptr<UpdateStack, USPtrDeleter>;
	std::string_view	_tableName;
    USPtr_t				_pUpdateStack{new UpdateStack(_tableName), USPtrDeleter(*this)};

public:
    USMgr(std::string_view tableName);
    /// Since UpdateStackManager handles the resource to the UpdateStack 
	/// object, UpdateStackManager will destroy the object
    ~USMgr() {
        /// _pUpdateStack should never be a nullptr at time of 
		/// UpdateStackManager destructor, but for sanity check...
        if(_pUpdateStack) {
            delete _pUpdateStack.release();
        }
    }

    // Don't copy
    USMgr(const USMgr&) = delete;
    USMgr& operator=(const USMgr&) = delete;

	constexpr std::string_view
	tableName() noexcept { return _tableName; }

    [[nodiscard]]
    USPtr_t
    getUpdateStack();
};

} // namespace gtd

#endif // __GTDBASE_HPP__
