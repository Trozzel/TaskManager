#include "GtdBase.hpp"

#include <utility>
#include "UpdateStack.hpp"
#include "GtdContainer.hpp"

namespace gtd {
/*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*/
//								GTDBASE CLASS
/*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*/

// CTORS
/*****************************************************************************/
GtdBase::GtdBase( const std::string_view name ) :
	_name(name)
{}

GtdBase::GtdBase(GtdBase&& other) noexcept :
	_name(std::move(other._name)),
	_o_uniqueId(other._o_uniqueId),
	_status(other._status),
	_created(other._created),
	_modified(other._modified),
	_o_parentId(other._o_parentId),
	_o_notes(std::move(other._o_notes))
{}

// DTOR
GtdBase::~GtdBase() noexcept = default;

// ASSIGMENT OPERATORS
/*****************************************************************************/
GtdBase&
GtdBase::operator=( GtdBase&& other ) noexcept {
	if(this != &other) {
		_name = std::move(other._name);
		_o_uniqueId = other._o_uniqueId;
		_status = other._status;
		_created = other._created;
		_modified = other._modified;
		_o_parentId = other._o_parentId;
		_o_notes = std::move(other._o_notes);
	}
	return *this;
}

// CONDITIONAL OPERATORS
/*****************************************************************************/
bool
GtdBase::operator==( const GtdBase& other ) const {
    if (&other == this) return true;
    return _name == other._name &&
        _o_uniqueId == other._o_uniqueId &&
        _status == other._status &&
        _created == other._created &&
        _modified == other._modified &&
        _o_parentId == other._o_parentId &&
        _o_notes == other._o_notes;
}

bool
GtdBase::operator!=( const GtdBase& other ) const {
    return !operator==(other);
}

// GETTERS
/*****************************************************************************/

// SETTERS
/*****************************************************************************/

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setName( const std::string_view name, const bool update ) {
	_name = name;
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setStatus( const std::string_view status, const bool update ) {
	_status = strToStatus(status);
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setStatus( const Status status, const bool update ) {
	_status = status;
}


void
GtdBase::setParent( const GtdBase& gtdItem, bool update ) {
	_o_parentId = gtdItem.uniqueId();
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setParentId( const unique_id_t id, const bool update ) {
	_o_parentId = id;
}

void
GtdBase::setParentId( const std::optional<unique_id_t> id, const bool update ) {
    _o_parentId = id;
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::GtdBase::setNotes( const std::string_view notes, const bool update ) { 
	_o_notes = notes;
}

/*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*/
//						       PULL OPERATORS
/*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*/
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
