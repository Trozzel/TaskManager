#include <stack>

#include "UpdateStack.hpp"
#include "GtdBase.hpp"
#include "GtdHelper.hpp"

namespace gtd {

// CLASS UpdateStack
/*****************************************************************************/

UpdateStack::UpdateStack() = default;

UpdateStack::~UpdateStack() = default;

void
UpdateStack::clear() {
	_dbUpdateStack = std::stack<stack_elem_t>();
}

void
UpdateStack::push( const unique_id_t uniqueId, std::string_view colName, const unique_id_t value) {
    _dbUpdateStack.emplace(uniqueId, colName, std::to_string(value));
}

void
UpdateStack::push( unique_id_t uniqueId, std::string_view colName, std::string_view value) {
    _dbUpdateStack.emplace(uniqueId, colName, std::string(value));
}

void
UpdateStack::push( unique_id_t uniqueId, std::string_view colName, std::string value) {
    _dbUpdateStack.emplace(uniqueId, colName, std::move(value));
}

void
UpdateStack::push( unique_id_t uniqueId, std::string_view colName, bool value) {
    _dbUpdateStack.emplace(uniqueId, colName, (value) ? "true" : "false");
}


void
UpdateStack::pop() {
	_dbUpdateStack.pop();
}

stack_elem_t&
UpdateStack::top() {
	return _dbUpdateStack.top();
}

std::string
UpdateStack::compose( const GtdBaseContainer& gtdItems ) {
    if ( gtdItems.empty() ) {
        return "WARNING: no items in " + gtdItems.tableName();
    }
    auto tableName = gtdItems.tableName();
    std::stringstream ss;
    ss << fmt::format("UPDATE {} SET ", gtdItems.tableName());
    while ( !_dbUpdateStack.empty() ) {
        const auto uniqueId = std::get<0>(_dbUpdateStack.top());
        const auto& pGtdItem = gtdItems.gtdItemByUniqueId(uniqueId);
        ss << topColName() << " = " << topValueStr();
        ss << " WHERE uniqueId = " << std::to_string(uniqueId) << ";";
        _dbUpdateStack.pop();
    }
    return ss.str();
}

// CLASS UpdateStackManager
/*****************************************************************************/
// 1. UpdateStackManager deleter for unique pointer
USMgr::
USPtrDeleter::USPtrDeleter(USMgr& usm) : _usMgr(usm) { }

void 
USMgr::
USPtrDeleter::operator()(UpdateStack* updateStackPtr) const {
	_usMgr._pUpdateStack.reset(updateStackPtr);
}

const USMgr::USPtr_t&
USMgr::getUpdateStack() const {
	return std::move(_pUpdateStack);
}

}  // namespace gtd
