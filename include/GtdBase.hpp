#ifndef GTDBASE_HPP_
#define GTDBASE_HPP_

#include <string>
#include <string_view>
#include <chrono>
#include <ranges>

#include "fmt/chrono.h" // Needed for timepoint_t to string

#include "GtdHelper.hpp"
#include "GtdBaseContainer.hpp"

namespace gtd {
class USMgr;

class GtdBase
{
protected:
    GtdBaseContainer&          _gtdItems;
    std::string                _name;
    std::optional<unique_id_t> _o_uniqueId{std::nullopt};
    Status                     _status{Status::Active};
    time_point_t               _created;
    time_point_t               _modified;
    std::optional<unique_id_t> _o_parentId{std::nullopt};
    std::optional<std::string> _o_notes{std::nullopt};

public:
    // CTORS
    /**************************************************************************/
    explicit GtdBase( GtdBaseContainer&, std::string_view name = "" );

    /// \brief declared as a virtual destructor. But since children will call
    /// this destructor, it is defined in GtdBase.cpp
    virtual ~GtdBase() = 0; // pure virtual destructor

    // Cannot copy an USMgr reference from another GtdBase, since GtdType must
    // be passed to the USMgr CTOR
    GtdBase&
    operator=( const GtdBase& );
    GtdBase&
    operator=( GtdBase&& ) noexcept;

    // GETTERS
    /**************************************************************************/
    [[nodiscard]]
    std::optional<unique_id_t>
    uniqueId() const noexcept {
        return _o_uniqueId;
    }

    [[nodiscard]]
    constexpr std::string_view
    name() const noexcept {
        return _name;
    } // implicit conversion to std::string_view

    [[nodiscard]]
    constexpr Status
    status() const noexcept {
        return _status;
    }

    [[nodiscard]]
    constexpr std::string_view
    statusStr() const noexcept {
        return statusToStr(_status);
    }

    [[nodiscard]]
    constexpr time_point_t
    created() const noexcept {
        return _created;
    }

    [[nodiscard]]
    std::string
    createdStr()
    const {
        return fmt::format("{}", _created);
    }

    [[nodiscard]]
    constexpr time_point_t
    modified() const noexcept {
        return _modified;
    }

    [[nodiscard]]
    std::string
    modifiedStr() const {
        return fmt::format("{}", _modified);
    }

    [[nodiscard]]
    std::optional<unique_id_t>
    parentId() const noexcept {
        return _o_parentId;
    }

    [[nodiscard]]
    std::optional<std::string_view>
    notes() const;

    // SETTERS
    /**************************************************************************/
    [[maybe_unused]]
    void
    setUniqueId( unique_id_t id ) noexcept {
        _o_uniqueId = id;
    }

    virtual void
    setName( std::string_view name, bool update = true );

    virtual void
    setStatus( std::string_view status, bool update = true );

    [[maybe_unused]]
    virtual void
    setStatus( Status status, bool update = true );

    virtual void
    setCreated( std::string_view created, bool update = true );

    [[maybe_unused]]
    virtual void
    setCreated( time_point_t tp, bool update = true );

    virtual void
    setModified( std::string_view modified, bool update = true );

    [[maybe_unused]]
    virtual void
    setModified( time_point_t tp, bool update = true );

    [[maybe_unused]]
    virtual void
    setParentId( unique_id_t id, bool update = true );

    [[maybe_unused]]
    virtual void
    setNotes( std::string_view notes, bool update = true );
};

std::ostream&
operator<<( std::ostream& out, const GtdBase& base );

/// GtdBaseContainer
/******************************************************************************/
} // namespace gtd

#endif // GTDBASE_HPP_
