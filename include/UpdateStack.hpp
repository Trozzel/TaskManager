//
// Created by George Ford on 12/14/23.
//

#ifndef UPDATESTACK_HPP_
#define UPDATESTACK_HPP_

#include <__concepts/arithmetic.h>
#include <_ctype.h>
#include <sstream>
#include <stack>
#include <type_traits>

#include "GtdHelper.hpp"
#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Exception.h"
#include "SQLiteCpp/Statement.h"
#include "fmt/base.h"
#include "fmt/format.h"
#include "gtd_concepts.hpp"

namespace gtd {
using ColName_t = std::string;
using ValueStr_t = std::string;
using id_col_val_t = std::tuple<unique_id_t, ColName_t, ValueStr_t>;

// CLASS UPDATE STACK
/*****************************************************************************/
template<cGtd Gtd_t>
class UpdateStack
{
protected:
	std::stack<std::string> _dbUpdateStack;

public:
    using value_type = std::stack<id_col_val_t>::value_type;
    using reference = std::stack<id_col_val_t>::reference;
    using const_reference = std::stack<id_col_val_t>::const_reference;

    UpdateStack() = default;

    ~UpdateStack() = default;

    UpdateStack( const UpdateStack& ) = delete;

    UpdateStack&
    operator=( const UpdateStack& ) = delete;

    static UpdateStack&
    getInstance() {
        static UpdateStack us;
        return us;
    }

    void
    clear() {
		_dbUpdateStack = std::stack<id_col_val_t>();
	}

    template <std::integral IntBool>
    void
    push( unique_id_t id, std::string_view colName, IntBool value ) 
	{
		auto statement = fmt::format("UPDATE {table} SET {col} = {val} WHERE uniqueId = {id}",
				fmt::arg("table", gtdTypeToTableName(Gtd_t::gtd_category::gtd_type)),
				fmt::arg("col",  colName), 
				fmt::arg("val",  value), 
				fmt::arg("id",   id)); 
		_dbUpdateStack.emplace(std::move(statement));
    }

    template <typename String>
    void
    push( unique_id_t id, std::string_view colName, String value )
        requires std::convertible_to<String, std::string_view>
	{
		auto statement = fmt::format("UPDATE {table} SET {col} = \"{val}\" WHERE uniqueId = {id}",
				fmt::arg("table", gtdTypeToTableName(Gtd_t::gtd_category::gtd_type)),
				fmt::arg("col",  colName), 
				fmt::arg("val",  value), 
				fmt::arg("id",   id)); 
		_dbUpdateStack.emplace(std::move(statement));
    }

    [[nodiscard]]
    constexpr size_t
    size() const {
        return _dbUpdateStack.size();
    }

    [[nodiscard]]
    constexpr unique_id_t
    topUniqueId() const {
        return std::get<0>(_dbUpdateStack.top());
    }

    [[nodiscard]]
    constexpr ColName_t
    topColName() const {
        return std::get<1>(_dbUpdateStack.top());
    }

    [[nodiscard]]
    constexpr const ValueStr_t&
    topValueStr() const {
        return std::get<2>(_dbUpdateStack.top());
    }

    void
    pop() {
		_dbUpdateStack.pop();
	}

    [[nodiscard]]
    const_reference
    top() const {
		return _dbUpdateStack.top();
	}

    size_t
    update( ) {
		// Amount of updated elements
		auto res = _dbUpdateStack.size();
		while(!_dbUpdateStack.empty()) {
			auto statement = std::move(_dbUpdateStack.top());
			fmt::println("To database: {}", statement);
			try {
				auto db = SQLite::Database(getDbConnPath(), SQLite::OPEN_READWRITE);
				auto qry = SQLite::Statement(db, statement);
				qry.exec();
			}
			catch (SQLite::Exception& e) {
				throw e.what();
			}
			_dbUpdateStack.pop();
		}
		return res;
	}
}; // class UpdateStack
} // namespace gtd

#endif //UPDATESTACK_HPP_
