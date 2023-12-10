#include "GtdBase.hpp"
#include <stack>

namespace gtd {

// CLASS UpdateStack
/*****************************************************************************/
// UpdateStack CTOR
UpdateStack::UpdateStack(std::string_view tableName) :
	_tableName(tableName) {}


void
UpdateStack::clear() {
	_dbUpdateStack = std::stack<update_pair_t>();
}

void
UpdateStack::push(const GtdBase& gtdItem, std::string_view colName) {
	/// uniqueId is only present in items that aleady exist in the database
	/// since the database assigns this value;
	/// Therefore, we can erase the bool 'update' flag and always update when
	/// the uniqueId is present
	if (gtdItem.uniqueId()) {
		_dbUpdateStack.push({*gtdItem.uniqueId(), colName});
	}
}

void
UpdateStack::pop() {
	_dbUpdateStack.pop();
}

update_pair_t&
UpdateStack::top() {
	return _dbUpdateStack.top();
}

std::string
UpdateStack::compose() {
	std::string retStr;
	std::stringstream ss;
	while(!_dbUpdateStack.empty()) {
		ss << "Id:  " << _dbUpdateStack.top().first << " ";
		ss << "Col: " << _dbUpdateStack.top().second << std::endl;
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
USPtrDeleter::operator()(UpdateStack* updateStackPtr) {
	_usMgr._pUpdateStack.reset(updateStackPtr);
}

// 2. UpdateStackManager
USMgr::USMgr(std::string_view tableName) :
	_tableName(tableName) {}

USMgr::USPtr_t
USMgr::getUpdateStack() {
	return std::move(_pUpdateStack);
}

} // namespae gtd
