#include <optional>

#include "GtdBase.hpp"
#include "UpdateStack.hpp"

namespace gtd {
// CTORS
/*****************************************************************************/
GtdBase::GtdBase( GtdBaseContainer& gtdItems, const std::string_view name ) :
    _gtdItems(gtdItems),
    _name(name)
{ }

// DTOR
// Must define destructor for inheriting classes
GtdBase::~GtdBase() = default;

// GETTERS
/*****************************************************************************/
std::optional<std::string_view>
GtdBase::notes() const {
    if ( _o_notes ) {
        return *_o_notes;
    }
    return std::nullopt;
}

// SETTERS
/*****************************************************************************/

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setName( std::string_view name, const bool update ) {
    _name = name;
    // Only updates if the Gtd_t object has a uniqueId (i.e. already present )
    if ( update ) {
        auto& usm = _gtdItems.updateStackManager();
        auto& pUpdateStack = usm.getUpdateStack();
        if(this->uniqueId()) {
            pUpdateStack->push(*this->uniqueId(), "name", name);
        }
    }
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setStatus( std::string_view status, const bool update ) {
    _status = strToStatus(status);
    if ( update ) {
        auto& usm = _gtdItems.updateStackManager();
        auto& pUpdateStack = usm.getUpdateStack();
        if(this->uniqueId()) {
            pUpdateStack->push(*this->uniqueId(), "status", statusStr());
        }
    }
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setStatus( const Status status, const bool update ) {
    _status = status;
    if ( update ) {
        auto& usm = _gtdItems.updateStackManager();
        auto& pUpdateStack = usm.getUpdateStack();
        if(this->uniqueId()) {
            pUpdateStack->push(*this->uniqueId(), "status", statusStr());
        }
    }
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setCreated( std::string_view created, const bool update ) {
    _created = strToTimePoint(created);
    if ( update ) {
        auto& usm = _gtdItems.updateStackManager();
        auto& pUpdateStack = usm.getUpdateStack();
        if(this->uniqueId()) {
            pUpdateStack->push(*this->uniqueId(), "created", createdStr());
        }
    }
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setCreated( const time_point_t tp, const bool update ) {
    _created = tp;
    if ( update ) {
        auto& usm = _gtdItems.updateStackManager();
        auto& pUpdateStack = usm.getUpdateStack();
        if(this->uniqueId()) {
            pUpdateStack->push(*this->uniqueId(), "created", createdStr());
        }
    }
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setModified( std::string_view modified, const bool update ) {
    _modified = strToTimePoint(modified);
    if ( update ) {
        auto& usm = _gtdItems.updateStackManager();
        auto& pUpdateStack = usm.getUpdateStack();
        if(this->uniqueId()) {
            pUpdateStack->push(*this->uniqueId(), "modified", modifiedStr());
        }
    }
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setModified( const time_point_t tp, const bool update ) {
    _modified = tp;
    if ( update ) {
        auto& usm = _gtdItems.updateStackManager();
        auto& pUpdateStack = usm.getUpdateStack();
        if(this->uniqueId()) {
            pUpdateStack->push(*this->uniqueId(), "modified", modifiedStr());
        }
    }
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::setParentId( const unique_id_t id, const bool update ) {
    _o_parentId = id;
    if ( update ) {
        auto& usm = _gtdItems.updateStackManager();
        auto& pUpdateStack = usm.getUpdateStack();
        if(this->uniqueId()) {
            pUpdateStack->push(*this->uniqueId(), "parentId", parentId());
        }
    }
}

/// \note implementation is handled in derived classes to write to DB upon
/// update
void
GtdBase::GtdBase::setNotes( std::string_view notes, const bool update ) {
    _o_notes = notes;
    if ( update ) {
        auto& usm = _gtdItems.updateStackManager();
        auto& pUpdateStack = usm.getUpdateStack();
        if(this->uniqueId()) {
            pUpdateStack->push(*this->uniqueId(), "notes", this->notes());
        }
    }
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
