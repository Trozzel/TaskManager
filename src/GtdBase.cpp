#include "GtdBase.hpp"
#include "UpdateStack.hpp"
#include "GtdContainer.hpp"

namespace gtd {
/*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*/
//								GTDBASE CLASS
/*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*/

// CTORS
/*****************************************************************************/
//GtdBase::GtdBase( pContainer gtdItems, const std::string_view name ) :
//    _gtdItems(gtdItems),
//    _name(name)
//{}

GtdBase::GtdBase( const std::string_view name ) :
	_name(name)
{}

GtdBase::GtdBase(GtdBase&& other) noexcept :
	_name(std::move(other._name)),
	_o_uniqueId(std::move(other._o_uniqueId)),
	_status(other._status),
	_created(other._created),
	_modified(other._modified),
	_o_parentId(std::move(other._o_parentId)),
	_o_notes(std::move(other._o_notes))
{}

// ASSIGMENT OPERATORS
/*****************************************************************************/
GtdBase&
GtdBase::operator=( GtdBase&& other ) noexcept {
	if(this != &other) {
		_name = std::move(other._name);
		_o_uniqueId = std::move(other._o_uniqueId);
		_status = other._status;
		_created = other._created;
		_modified = other._modified;
		_o_parentId = std::move(other._o_parentId);
		_o_notes = std::move(other._o_notes);
	}
	return *this;
}

// GETTERS
/*****************************************************************************/

// SETTERS
/*****************************************************************************/

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setName( const std::string_view name, const bool update ) {
	if constexpr (gtd_category::constructible) {
		_name = name;
		if ( update ) {
			auto& us = _gtdItems->updateStack();
			if(this->uniqueId()) {
				us.push(*uniqueId(), "name", name);
			}
		}
	}
	else {
		std::cerr << "'*this' must gtd_category::constructible == true\n";
	}
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setStatus( const std::string_view status, const bool update ) {
	if constexpr (gtd_category::constructible) {
		_status = strToStatus(status);
		if ( update ) {
			auto& us = _gtdItems->updateStack();
			if(this->uniqueId()) {
				us.push(*uniqueId(), "status", statusStr());
			}
		}
	}
	else {
		std::cerr << "'*this' must gtd_category::constructible == true\n";
	}
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setStatus( const Status status, const bool update ) {
	if constexpr (gtd_category::constructible) {
		_status = status;
		if ( update ) {
			auto& us = _gtdItems->updateStack();
			if(uniqueId()) {
				us.push(*uniqueId(), "status", statusStr());
			}
		}
	}
	else {
		std::cerr << "'*this' must gtd_category::constructible == true\n";
	}
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setCreated( const std::string_view created, const bool update ) {
	if constexpr (gtd_category::constructible) {
		_created = strToTimePoint(created);
		if ( update ) {
			auto& us = _gtdItems->updateStack();
			if(uniqueId()) {
				us.push(*uniqueId(), "created", createdStr());
			}
		}
	}
	else {
		std::cerr << "'*this' must gtd_category::constructible == true\n";
	}
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setCreated( const time_point_t tp, const bool update ) {
	if constexpr (gtd_category::constructible) {
		_created = tp;
		if ( update ) {
			auto& us = _gtdItems->updateStack();
			if(this->uniqueId()) {
				us.push(*uniqueId(), "created", createdStr());
			}
		}
	}
	else {
		std::cerr << "'*this' must gtd_category::constructible == true\n";
	}
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setModified( const std::string_view modified, const bool update ) {
	if constexpr (gtd_category::constructible) {
		_modified = strToTimePoint(modified);
		if ( update ) {
			auto& us = _gtdItems->updateStack();
			if(uniqueId()) {
				us.push(*uniqueId(), "modified", modifiedStr());
			}
		}
	}
	else {
		std::cerr << "'*this' must gtd_category::constructible == true\n";
	}
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setModified( const time_point_t tp, const bool update ) {
	if constexpr (gtd_category::constructible) {
		_modified = tp;
		if ( update ) {
			auto& us = _gtdItems->updateStack();
			if(uniqueId()) {
				us.push(*uniqueId(), "modified", modifiedStr());
			}
		}
	}
	else {
		std::cerr << "'*this' must gtd_category::constructible == true\n";
	}
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setParentId( const unique_id_t id, const bool update ) {
	if constexpr (gtd_category::constructible) {
		_o_parentId = id;
		if ( update ) {
			auto& us = _gtdItems->updateStack();
			if(uniqueId()) {
				us.push(*uniqueId(), "parentId", *parentId());
			}
		}
	}
	else {
		std::cerr << "'*this' must gtd_category::constructible == true\n";
	}
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::GtdBase::setNotes( const std::string_view notes, const bool update ) {
	if constexpr (gtd_category::constructible) {
		_o_notes = notes;
		if ( update ) {
			auto& us = _gtdItems->updateStack();
			if(uniqueId()) {
				us.push(*uniqueId(), "notes", *this->notes());
			}
		}
	}
	else {
		std::cerr << "'*this' must gtd_category::constructible == true\n";
	}
}

/*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*/
//							CONTEXT CLASS
/*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*/
// CTORS
/*************************************************************************/
Context::Context( const pContainer gtdItems, const std::string_view name ) :
	GtdBase(name),
	_gtdItems(gtdItems)
{}

Context::Context( Context&& other ) :
	GtdBase(other),
	_gtdItems(std::move(other._gtdItems))
{}

// ASSIGMENT OPERATORS
/*************************************************************************/
Context&
Context::operator=( Context&& other ) {
	if(this != &other) {
		GtdBase::operator=(other);
		_gtdItems = std::move(other._gtdItems);
	}
	return *this;
}

/*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*/
//							FOLDER CLASS
/*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*/
// CTORS
/*************************************************************************/
Folder::Folder( const pContainer gtdItems, const std::string_view name ) :
	GtdBase(name),
	_gtdItems(gtdItems)
{}

Folder::Folder( Folder&& other ) :
	GtdBase(other),
	_gtdItems(std::move(other._gtdItems))
{}

// ASSIGMENT OPERATORS
/*************************************************************************/
Folder&
Folder::operator=( Folder&& other ) {
	if(this != &other) {
		GtdBase::operator=(other);
		_gtdItems = std::move(other._gtdItems);
	}
	return *this;
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
