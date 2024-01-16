#ifndef GTDBASE_HPP_
#define GTDBASE_HPP_

#include <chrono>

#include "fmt/chrono.h" // Needed for timepoint_t to string

#include "GtdHelper.hpp"

namespace gtd {

// FORWARD DECLARATIONS	
/*****************************************************************************/
class GtdBase;

template<typename Gtd_t>
class GtdContainer;

/*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*/
//							GTDBASE CLASS
/*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*/
class GtdBase
{
public:
	// Class traits
	using gtd_category = base_tag; 
private:
	// Hide from inheriting classes
protected:
    std::string							 _name;
    std::optional<unique_id_t> 			 _o_uniqueId {std::nullopt};
    Status                     			 _status {Status::Active};
    time_point_t               			 _created;
    time_point_t               			 _modified;
    std::optional<unique_id_t> 			 _o_parentId {std::nullopt};
    std::optional<std::string> 			 _o_notes {std::nullopt};

public:
    // CTORS
    /**************************************************************************/
	explicit GtdBase( std::string_view name);
	GtdBase(const GtdBase&) = default;
	GtdBase(GtdBase&&) noexcept;
    virtual ~GtdBase() noexcept = 0;

    GtdBase&
    operator=( const GtdBase& ) = default;
    GtdBase&
    operator=( GtdBase&& ) noexcept;

    // COMPARISON OPERATORS
    /*************************************************************************/
    bool
    operator==(const GtdBase&) const;

    bool
    operator!=(const GtdBase&) const;

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
    notes() const {
		return _o_notes;
	}

    // SETTERS
    /*************************************************************************/
    constexpr void
    setUniqueId( const unique_id_t id ) noexcept {
        _o_uniqueId = id;
    }

    virtual void
    setName( std::string_view name, bool update );

    virtual void
    setStatus( std::string_view status, bool update );

    [[maybe_unused]]
    virtual void
    setStatus( Status status, bool update );

    [[maybe_unused]]
    virtual void
    setParentId( unique_id_t id, bool update );

    [[maybe_unused]]
    virtual void
    setNotes( std::string_view notes, bool update );
};

} // namespace gtd

std::ostream&
operator<<( std::ostream& out, const gtd::GtdBase& base );

#endif // GTDBASE_HPP_
