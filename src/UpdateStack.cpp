#include "UpdateStack.hpp"
#include "GtdBase.hpp"
#include "GtdHelper.hpp"

namespace gtd {

// CLASS UpdateStack
/*****************************************************************************/

void
UpdateStack::clear() {
	_dbUpdateStack = std::stack<id_col_val_t>();
}

void
UpdateStack::push( const unique_id_t uniqueId, const std::string_view colName, const bool value) {
    _dbUpdateStack.emplace(uniqueId, colName, (value) ? "true" : "false");
}


void
UpdateStack::pop() {
	_dbUpdateStack.pop();
}

id_col_val_t const &
UpdateStack::top() const {
	return _dbUpdateStack.top();
}

//std::string
//UpdateStack::compose( const GtdContainer& gtdItems ) {
//    if ( gtdItems.empty() ) {
//        return "WARNING: no items in " + gtdItems.tableName();
//    }
//    auto tableName = gtdItems.tableName();
//    std::stringstream ss;
//    ss << fmt::format("UPDATE {} SET ", gtdItems.tableName());
//    while ( !_dbUpdateStack.empty() ) {
//        const auto uniqueId = std::get<0>(_dbUpdateStack.top());
//        const auto& pGtdItem = gtdItems.gtdItemByUniqueId(uniqueId);
//        ss << topColName() << " = " << topValueStr();
//        ss << " WHERE uniqueId = " << std::to_string(uniqueId) << ";";
//        _dbUpdateStack.pop();
//    }
//    return ss.str();
//}

}  // namespace gtd
