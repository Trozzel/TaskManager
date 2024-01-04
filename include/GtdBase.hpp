#ifndef GTDBASE_HPP_
#define GTDBASE_HPP_

#include <optional>
#include <string>
#include <string_view>
#include <chrono>
#include <ranges>
#include <type_traits>

#include "fmt/chrono.h" // Needed for timepoint_t to string

#include "GtdHelper.hpp"
#include "gtd_concepts.hpp"
#include "GtdBaseContainer.hpp"

namespace gtd {
class USMgr;

template <GtdType gtdType>
class GtdBase
{
protected: // Helper functions
    template <SqliteType Value_t>
    void
    pushToUpdateStack( std::string_view colName, Value_t value, const bool update ) const {
        // Ensure that Value_t is one of the accepted types
        if ( update ) {
            auto& usm          = _gtds.updateStackManager();
            auto& pUpdateStack = usm.getUpdateStack();
            if ( this->uniqueId() ) {
                pUpdateStack->push(*this->uniqueId(), colName, value);
            }
        }
    }

protected:
	// BASE MEMBERS
	GtdType					   _gtdType{gtdType};
    GtdContainer<GtdBase>&     _gtds;
    std::string                _name;
    std::optional<unique_id_t> _o_uniqueId{std::nullopt};
    Status                     _status{Status::Active};
    time_point_t               _created;
    time_point_t               _modified;
    std::optional<unique_id_t> _o_parentId{std::nullopt};
    std::optional<std::string> _o_notes{std::nullopt};

public:
	static constexpr const char*
	tableName() {
		if      constexpr(gtdType == GtdType::Context) return "contexts";
		else if constexpr(gtdType == GtdType::Folder)  return "folders";
		else if constexpr(gtdType == GtdType::Task)    return "tasks";
		else if constexpr(gtdType == GtdType::Project) return "projects";
	}
    // CTORS
    /**************************************************************************/
    explicit
    GtdBase( GtdContainer<GtdBase>& gtds, const std::string_view name = "" ) :
        _gtds(gtds),
        _name(name) 
	{
        _gtds.push_back(*this);
    }

    GtdBase( const GtdBase& other ) :
        _gtds(other._gtds),
        _name(other._name),
        _o_uniqueId(other._o_uniqueId),
        _status(other._status),
        _o_parentId(other._o_parentId),
        _o_notes(other._o_notes) 
	{
        _gtds.push_back(*this);
    }

    GtdBase( GtdBase&& other ) :
        _gtds(other._gtds),
		_name(std::move(other._name)),
		_o_uniqueId(std::move(other._o_uniqueId)),
		_status(other._status),
		_created(other._created),
		_modified(other._modified),
		_o_parentId(std::move(other._o_parentId)),
		_o_notes(std::move(other._o_notes))
	{
		_gtds.push_back(*this);
	}

    virtual ~GtdBase() {
        fmt::println("Removing {} from Container", name());
        _gtds.erase(*this);
    }

    GtdBase&
    operator=( const GtdBase& other )
    {
        if(this != &other) {
            _gtds = other._gtds;
            _name = other._name;
            _o_uniqueId = other._o_uniqueId;
            _status = other._status;
            _o_parentId = other._o_parentId;
            _o_notes = other._o_notes;
            _gtds.push_back(*this);
        }
        return *this;
    }

    GtdBase&
    operator=( GtdBase&& other ) noexcept 
	{
		if(this != &other) {
			_gtds = other._gtds;
			_name = std::move(other._name);
			_o_uniqueId = std::move(other._o_uniqueId);
			_status = other._status;
			_created = other._created;
			_modified = other._modified;
			_o_parentId = std::move(other._o_parentId);
			_o_notes = std::move(other._o_notes);
			_gtds.push_back(*this);
		}
		return *this;
	}

    // GETTERS
    /**************************************************************************/
    [[nodiscard]]
    constexpr std::optional<unique_id_t>
    uniqueId() const noexcept {
        return _o_uniqueId;
    }

    [[nodiscard]]
    constexpr std::string_view
    name() const noexcept {
        return _name;
    }

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
    /**************************************************************************/
    [[maybe_unused]]
    void
    setUniqueId( const unique_id_t id ) noexcept {
        _o_uniqueId = id;
    }

	void
    setName( const std::string_view name, const bool update = true ) {
		_name = name;
		// Only updates if the Gtd_t object has a uniqueId (i.e. already present )
		pushToUpdateStack("name", this->name(), update);
	}

    void
    setStatus( const std::string_view status, const bool update = true ) {
		_status = strToStatus(status);
		pushToUpdateStack("status", _status, update);
	}

    [[maybe_unused]]
    void
    setStatus( const Status status, const bool update = true ) {
		_status = status;
		pushToUpdateStack("status", statusStr(), update);
	}

    void
    setCreated( const std::string_view created, const bool update = true ) {
		_created = strToTimePoint(created);
		pushToUpdateStack("created", createdStr(), update);
	}

    [[maybe_unused]]
    void
    setCreated( const time_point_t tp, const bool update = true ) {
		_created = tp;
		pushToUpdateStack("created", createdStr(), update);
	}

    void
    setModified( const std::string_view modified, const bool update = true ){
		_modified = strToTimePoint(modified);
		pushToUpdateStack("modified", this->modifiedStr(), update);
	}

    [[maybe_unused]]
    void
    setModified( const time_point_t tp, const bool update = true ) {
		_modified = tp;
		pushToUpdateStack("modified", this->modifiedStr(), update);
	}

    [[maybe_unused]]
    void
    setParentId( unique_id_t id, bool update = true ) {
		_o_parentId = id;
		pushToUpdateStack("parentId", parentId(), update);
	}

    [[maybe_unused]]
    void
    setNotes( std::string_view notes, bool update = true ) {
		_o_notes = notes;
		pushToUpdateStack("notes", this->notes(), update);
	}

};

static_assert(IsGtdBase<GtdBase<GtdType::Context>>);
static_assert(IsGtdBase<GtdBase<GtdType::Folder>>);


template<GtdType gtdType>
std::ostream&
operator<<( std::ostream& out, const GtdBase<gtdType>& gtd ) {
	out << "TASK: '" << gtd.name() << "'\n'";
	return out;
}

/******************************************************************************/
} // namespace gtd

#endif // GTDBASE_HPP_
