#include <optional>

#include "GtdBase.hpp"

namespace gtd {

// CTORS
/*****************************************************************************/
Gtd::Gtd( GtdContainer& gtdItems, const std::string_view name ) :
    _gtds(gtdItems),
    _name(name)
{ }

// DTOR
Gtd::~Gtd() = default;

// GETTERS
/*****************************************************************************/
std::optional<std::string_view>
Gtd::notes() const {
    if ( _o_notes ) {
        return *_o_notes;
    }
    return std::nullopt;
}

// SETTERS
/*****************************************************************************/

void
Gtd::setName( std::string_view name, const bool update ) {
    _name = name;
    // Only updates if the Gtd_t object has a uniqueId (i.e. already present )
    pushToUpdateStack("name", this->name(), update);
}

void
Gtd::setStatus( std::string_view status, const bool update ) {
    _status = strToStatus(status);
    pushToUpdateStack("status", _status, update);
}

void
Gtd::setStatus( const Status status, const bool update ) {
    _status = status;
    pushToUpdateStack("status", statusStr(), update);
}

void
Gtd::setCreated( std::string_view created, const bool update ) {
    _created = strToTimePoint(created);
    pushToUpdateStack("created", createdStr(), update);
}

void
Gtd::setCreated( const time_point_t tp, const bool update ) {
    _created = tp;
    pushToUpdateStack("created", createdStr(), update);
}

void
Gtd::setModified( std::string_view modified, const bool update ) {
    _modified = strToTimePoint(modified);
    pushToUpdateStack("modified", this->modifiedStr(), update);
}

void
Gtd::setModified( const time_point_t tp, const bool update ) {
    _modified = tp;
    pushToUpdateStack("modified", this->modifiedStr(), update);
}

void
Gtd::setParentId( const unique_id_t id, const bool update ) {
    _o_parentId = id;
    pushToUpdateStack("parentId", parentId(), update);
}

void
Gtd::setNotes( std::string_view notes, const bool update ) {
    _o_notes = notes;
    pushToUpdateStack("notes", this->notes(), update);
}

// PULL OPERATOR FOR OSTREAM
std::ostream&
operator<<( std::ostream& out, const GtdBase& base ) {
    out << *base.uniqueId() << " " << base.name() << " "
            << base.statusStr() << " "
            << base.createdStr() << " "
            << base.modifiedStr() << " "
            << *base.parentId();

    return out;
}

} // namespace gtd
