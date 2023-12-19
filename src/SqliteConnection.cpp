//
// Created by George Ford on 12/11/23.
//

#include <exception>
#include <string_view>
#include <sys/stat.h>

#include "SQLiteCpp/Statement.h"
#include "SqliteConnection.hpp"
#include "SQLiteCpp/Database.h"

SqliteConnection::SqliteConnection(std::string_view dbPath, int flags) :
	DbBase(dbPath),
	_flags(flags),
	_db(dbPath, flags)
{
}

int
SqliteConnection::exec(std::string_view queries) {
	int numElemChanged = 0;
	try {
		auto db = SQLite::Database(_uri, _flags);
		numElemChanged = db.exec(queries.data());
	}
	catch (std::exception& e) {
		std::cerr << "SQLite exec() error: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	return numElemChanged;
}

void
SqliteConnection::reset(int flags) {
	_db = std::move(SQLite::Database(_uri, flags));
}

SQLite::Statement
SqliteConnection::getStatement(std::string_view statement) {
	return SQLite::Statement(_db, statement.data());
}

auto
SqliteConnection::executeStep() {
	
}
