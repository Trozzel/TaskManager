//
// Created by George Ford on 1/9/24.
//

#include "Folder.hpp"

#include "GtdContainer.hpp"

namespace gtd {
// CTORS
/*************************************************************************/
Folder::Folder( const sp_Container& folders, const std::string_view name ) :
    GtdBase(name),
    _folders(folders) {}

// ASSIGMENT OPERATORS
/*****************************************************************************/
Folder&
Folder::operator=( const Folder& other ) {
    if ( this != &other ) {
        GtdBase::operator=(other);
        _folders = other._folders;
    }
    return *this;
}

// COMPARISON OPERATORS
/*****************************************************************************/
bool
Folder::operator==( const Folder& other ) const {
    // TODO: determine way to test for weak_ptr equality
    return GtdBase::operator==(other) ;
}

bool
Folder::operator!=( const Folder& other ) const {
    return GtdBase::operator!=(other) ;
}

// OVERRIDE SETTERS
/*****************************************************************************/
void
Folder::setName( const std::string_view name, const bool update ) {
    GtdBase::setName(name, update);
    if ( update ) {
        auto& us = _folders.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*uniqueId(), "name", this->name());
        }
    }
}

void
Folder::setStatus( const std::string_view status, const bool update ) {
    GtdBase::setStatus(status, update);
    if ( update ) {
        auto& us = _folders.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*uniqueId(), "status", statusStr());
        }
    }
}

void
Folder::setStatus( const Status status, const bool update ) {
    GtdBase::setStatus(status, update);
    if ( update ) {
        auto& us = _folders.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*uniqueId(), "status", statusStr());
        }
    }
}

void
Folder::setParentId( const unique_id_t id, const bool update ) {
    GtdBase::setParentId(id, update);
    if ( update ) {
        auto& us = _folders.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*uniqueId(), "parentId", *this->parentId());
        }
    }
}

void
Folder::setParentId( std::optional<unique_id_t> id, bool update ) {
    GtdBase::setParentId(id, update);
    if ( update ) {
        auto& us = _folders.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*uniqueId(), "parentId", *this->parentId());
        }
    }
}

void
Folder::setNotes( const std::string_view notes, const bool update ) {
    GtdBase::setNotes(notes, update);
    if ( update ) {
        auto& us = _folders.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*uniqueId(), "notes", *this->notes());
        }
    }
}

} // namespace gtd
