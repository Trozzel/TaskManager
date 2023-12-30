//
// Created by George Ford on 12/11/23.
//

#include <string_view>

#include "SQLiteCpp/Statement.h"
#include "SqliteConnection.hpp"

#include <Context.hpp>

#include "SQLiteCpp/Database.h"

namespace gtd {
SqliteConnection::SqliteConnection( std::string_view dbPath, const int flags ) :
    DbBase(dbPath),
    _flags(flags) {}

SqliteConnection::~SqliteConnection() = default;

unique_id_t
SqliteConnection::getLastInsertId() {
    try {
        SQLite::Database db(_uri, _flags);
        return db.getLastInsertRowid();
    }
    catch ( SQLite::Exception& e ) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw std::runtime_error("Error acquiring last insert id from db");
    }
}

int
SqliteConnection::execute( std::string_view queries ) {
    int res{};
    try {
        SQLite::Database db(_uri, _flags);
        res = db.exec(queries.data());
    }
    catch ( SQLite::Exception& e ) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw std::runtime_error("Error executing: " + std::string(queries));
    }
    return res;
}

bool
SqliteConnection::executeStep() {}

void
SqliteConnection::connect() {
    SQLite::Database db(_uri, _flags);
}

bool
SqliteConnection::close() {}

int
SqliteConnection::createGtd( std::string_view table, const pGtdBase_t& ) {}

int
SqliteConnection::importAllBase( GtdBaseContainer& gtdItems ) {
    int count = 0;
    try {
        SQLite::Database  db(_uri, _flags);
        SQLite::Statement query(db, fmt::format(" SELECT * FROM {}", gtdItems.tableName()));
        for ( ; query.executeStep(); ++count ) {
            constexpr bool dontUpdate = false;
            int            colNum     = 0;
            pBase->setUniqueId(query.getColumn(colNum++).getInt64());
            pBase->setName(query.getColumn(colNum++).getString(), dontUpdate);
            if ( !query.isColumnNull(colNum++) ) {
                pBase->setParentId(query.getColumn(colNum - 1).getInt64(), dontUpdate);
            }
            pBase->setStatus(std::string_view(query.getColumn(colNum++).getString()), dontUpdate);
            pBase->setCreated(std::string_view(query.getColumn(colNum++).getString()), dontUpdate);
            pBase->setModified(std::string_view(query.getColumn(colNum++).getString()), dontUpdate);
            pBase->setNotes(query.getColumn(colNum++).getString(), dontUpdate);
            gtdItems.push_back(std::move(pBase));
        }
    }
    catch ( SQLite::Exception& e ) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw std::runtime_error(fmt::format("Error importing {}", gtdItems.tableName()));
    }
    return count;
}

int
SqliteConnection::importAllFolder( FolderContainer& ) {}

int
SqliteConnection::importAllTask( TaskContainer& ) {}

int
SqliteConnection::importAllProject( ProjectContainer& ) {}

bool
SqliteConnection::insertContext( std::string_view table, const pContext_t& ) {}

bool
SqliteConnection::insertFolder( std::string_view table, const pFolder_t& ) {}

bool
SqliteConnection::insertTask( std::string_view table, const pTask_t& ) {}

bool
SqliteConnection::insertProject( std::string_view table, const pProject_t& ) {}

bool
SqliteConnection::deleteOne( std::string_view table, const pGtdBase_t& ) {}
} // namespace gtd
