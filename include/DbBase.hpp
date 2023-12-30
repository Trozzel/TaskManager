//
// Created by George Ford on 12/11/23.
//
#ifndef DBBASE_HPP_
#define DBBASE_HPP_
#include <GtdHelper.hpp>
#include <string_view>

#include "GtdBaseContainer.hpp"
#include "ContextContainer.hpp"
#include "FolderContainer.hpp"
#include "TaskContainer.hpp"
#include "ProjectContainer.hpp"

// Forward declaration of GtdBaseContainer for importing and updating records
namespace gtd {
class DbBase
{
protected:
    std::string_view _uri;

public:
    explicit
    DbBase( std::string_view uri );
    virtual ~DbBase() = 0;

    virtual void
    connect() = 0;

    virtual bool
    close() = 0;

    [[nodiscard]]
    virtual unique_id_t
    getLastInsertId() = 0;

    virtual int
    execute( std::string_view queries ) = 0;

    virtual bool
    executeStep() = 0;

    virtual int
    createGtd( std::string_view table, const pGtdBase_t& ) = 0;

    virtual int
    importAll( GtdBaseContainer& ) = 0;

    virtual int
    importAllBase( GtdBaseContainer& ) = 0;

    virtual int
    importAllFolder( FolderContainer& ) = 0;

    virtual int
    importAllTask( TaskContainer& ) = 0;

    virtual int
    importAllProject( ProjectContainer& ) = 0;

    virtual bool
    insertContext( std::string_view table, const pContext_t& ) = 0;

    virtual bool
    insertFolder( std::string_view table, const pFolder_t& ) = 0;

    virtual bool
    insertTask( std::string_view table, const pTask_t& ) = 0;

    virtual bool
    insertProject( std::string_view table, const pProject_t& ) = 0;

    virtual bool
    deleteOne( std::string_view table, const pGtdBase_t& ) = 0;
};
} // namespace gtd


#endif //DBBASE_HPP_
