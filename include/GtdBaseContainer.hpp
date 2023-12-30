//
// Created by George Ford on 12/16/23.
//
#ifndef GTDBASECONTAINER_HPP_
#define GTDBASECONTAINER_HPP_

#include <DbBase.hpp>
#include <vector>

#include "GtdHelper.hpp"
#include "UpdateStack.hpp"

namespace gtd {
class GtdBase;

using pGtdBase_t = std::unique_ptr<GtdBase>;

/// \brief Class that contains vector of GtdBase objects. Facilitates
/// inter-GtdBase interactions
class GtdBaseContainer
{
protected:
    std::vector<pGtdBase_t>      _gtdItems{};
    USMgr&                       _usMgr;
    std::unique_ptr<DbBase>      _dbCon = nullptr;

public:
    // Type definitions
    using value_type = std::vector<pGtdBase_t>::value_type;
    using iterator = std::vector<pGtdBase_t>::iterator;
    using const_iterator = std::vector<pGtdBase_t>::const_iterator;
    using size_type = std::vector<pGtdBase_t>::size_type;
    using difference_type = std::vector<pGtdBase_t>::difference_type;

    // CTORS
    explicit
    GtdBaseContainer( USMgr& );
    GtdBaseContainer( USMgr&, std::unique_ptr<DbBase> );
    GtdBaseContainer( USMgr&, DbBase* );

    // ~GtdBaseContainer() = default in source file for inheriting classes
    virtual ~GtdBaseContainer() = 0;

    GtdBaseContainer( const GtdBaseContainer& ) = delete;

    GtdBaseContainer&
    operator=( const GtdBaseContainer& ) = delete;

    [[nodiscard]]
    virtual const std::string&
    tableName() const;

    [[nodiscard]]
    const USMgr&
    updateStackManager() const;

    [[nodiscard]]
    virtual auto
    begin();

    [[nodiscard]]
    virtual auto
    cbegin() const;

    [[nodiscard]]
    virtual auto
    end();

    [[nodiscard]]
    virtual auto
    cend() const;

    virtual const pGtdBase_t&
    operator[]( size_t idx ) const;

    [[nodiscard]] virtual const pGtdBase_t&
    at( size_t ) const;

    virtual void
    push_back( GtdBase* );

    virtual void
    push_back( pGtdBase_t );

    [[nodiscard]] virtual const pGtdBase_t&
    gtdItemByUniqueId( unique_id_t ) const;

    [[nodiscard]] bool
    empty() const;

    [[nodiscard]] std::ranges<pGtdBase_t> // view to _gtdBases
    getBeforeCreated( time_point_t ) const;

    [[nodiscard]] std::ranges<pGtdBase_t> // view to _gtdBases
    getBeforeCreated( const GtdBase& ) const;

    [[nodiscard]] std::ranges<pGtdBase_t> // view to _gtdBases
    getAfterCreated( time_point_t ) const;

    [[nodiscard]] std::ranges<pGtdBase_t> // view to _gtdBases
    getAfterCreated( const GtdBase& ) const;

    /// \brief Import all elements from given table into container
    virtual bool
    importAllFromDb() = 0;

    /// \return number of elements
    [[nodiscard]] virtual int
    updateToDb() const;
};
} // namespace gtd

#endif //GTDBASECONTAINER_HPP_
