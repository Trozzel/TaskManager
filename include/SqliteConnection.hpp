//
// Created by George Ford on 12/11/23.
//

#ifndef SQLITECONNECTION_HPP_
#define SQLITECONNECTION_HPP_

#include "GtdHelper.hpp"
#include "SQLiteCpp/Database.h"
#include "DbBase.hpp"
#include "SQLiteCpp/Statement.h"
#include <string>
#include <string_view>
#include <sys/_types/_size_t.h>
#include <type_traits>

class SqliteConnection : public DbBase {
private:
	SQLite::Database        _db;
	int     				_flags = SQLite::OPEN_READONLY;

public:
	SqliteConnection(std::string_view dbPath, int flags = SQLite::OPEN_READONLY);
	~SqliteConnection() override = default;

	/// \brief performs immediate transaction on database
	/// \return number of elements changed
	int  
	exec(std::string_view queries) override;

	void
	reset(int flags);

	SQLite::Statement
	getStatement(std::string_view statement);

	void
	setStatement(std::string_view statementStr);

	template<typename Int_t>
	unsigned long long
	getColumn(size_t rowNum, std::enable_if_t<std::is_integral_v<Int_t>, bool> = true);

	template<typename ConstChar_t>
	std::string
	getColumn(size_t rowNum, std::enable_if_t<std::is_same_v<const char*, ConstChar_t>, bool> = true);

	template<typename StdString_t>
	std::string
	getColumn(size_t rowNum, std::enable_if_t<std::is_same_v<
			std::remove_const_t<std::remove_reference_t<StdString_t>>, std::string>, bool> = true);
	
	bool
	isColumnNull() const;

	auto
	executeStep();
	
};



#endif // SQLITECONNECTION_HPP
