//
// Created by George Ford on 12/11/23.
//

#ifndef SQLITECONNECTION_HPP_
#define SQLITECONNECTION_HPP_

#include "SQLiteCpp/Database.h"
#include "DbBase.hpp"
#include "SQLiteCpp/Statement.h"
#include <string_view>
#include <sys/_types/_size_t.h>
#include <type_traits>

template<typename T>
concept sqlite_type = std::is_integral_v<T> ||
                      std::is_convertible_v<T, std::string_view> ||
                      std::is_null_pointer_v<T>;
namespace gtd {
class SqliteConnection : public DbBase {
private:
    int         _flags;
public:
    explicit SqliteConnection(std::string_view dbPath, int flags = SQLite::OPEN_READWRITE);
    ~SqliteConnection() override;

    [[nodiscard]] unique_id_t
    getLastInsertId() override;

    int
    execute( std::string_view queries ) override;

    bool
    executeStep() override;

    void
    connect() override;

    bool
    close() override;

    int
    createGtd( std::string_view table, const pGtdBase_t& ) override;

    int
    importAllBase( GtdBaseContainer& ) override;

    int
    importAllFolder( FolderContainer& ) override;

    int
    importAllTask( TaskContainer& ) override;

    int
    importAllProject( ProjectContainer& ) override;

    bool
    insertContext( std::string_view table, const pContext_t& ) override;

    bool
    insertFolder( std::string_view table, const pFolder_t& ) override;

    bool
    insertTask( std::string_view table, const pTask_t& ) override;

    bool
    insertProject( std::string_view table, const pProject_t& ) override;

    bool
    deleteOne( std::string_view table, const pGtdBase_t& ) override;
};
} // namespace gtd

#endif // SQLITECONNECTION_HPP_
