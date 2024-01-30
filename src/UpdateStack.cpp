#include "UpdateStack.hpp"

namespace gtd {

// CLASS UpdateStack
/*****************************************************************************/

void
UpdateStack::clear() {
	_dbUpdateStack = std::stack<id_col_val_t>();
}

void
UpdateStack::push( const unique_id_t id, const std::string_view colName, const bool value ) {
	_dbUpdateStack.emplace(id, colName, (value) ? "true" : "false");
}

constexpr ColName_t
UpdateStack::topColName() const {
	return std::get<1>(_dbUpdateStack.top());
}

constexpr const ValueStr_t&
UpdateStack::topValueStr() const {
	return std::get<2>(_dbUpdateStack.top());
}

void
UpdateStack::pop() {
	_dbUpdateStack.pop();
}

UpdateStack::const_reference
UpdateStack::top() const {
	return _dbUpdateStack.top();
}

std::string
UpdateStack::compose(GtdType gtdType)
{
    std::string res{};
    fmt::println("Table name: {}", gtdTypeToTableName(gtdType));
    while(!_dbUpdateStack.empty()) {
        res += fmt::format("ID: {}, COLUMN: {}, VALUE: {}\n",
                std::get<0>(_dbUpdateStack.top()), 
                std::get<1>(_dbUpdateStack.top()),
                std::get<2>(_dbUpdateStack.top()));
        _dbUpdateStack.pop();
    }
    return res;
}

}  // namespace gtd
