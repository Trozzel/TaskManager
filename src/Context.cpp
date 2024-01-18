//
// Created by George Ford on 1/9/24.
//

#include "Context.hpp"
#include "GtdContainer.hpp"
#include "GtdBase.hpp"
#include <string_view>
#include <utility>

namespace gtd {
// CTORS
/*************************************************************************/
Context::Context( const sp_Container& contexts, const std::string_view name ) :
    GtdBase(name),
    _contexts(contexts) { }

Context::Context( Context&& other ) noexcept:
    GtdBase(std::move(other)) {
    _contexts = other._contexts;
}

// ASSIGMENT OPERATORS
/*************************************************************************/
Context&
Context::operator=( const Context& other ) {
    if ( this != &other ) {
        GtdBase::operator=(other);
        _contexts = other._contexts;
    }
    return *this;
}

Context&
Context::operator=( Context&& other ) noexcept {
    if ( this != &other ) {
        GtdBase::operator=(std::move(other));
        _contexts = other._contexts;
    }
    return *this;
}

// COMPARISON OPERATORS
/*************************************************************************/
bool
Context::operator==( const Context& other ) const {
    return GtdBase::operator==(other);
}

bool
Context::operator!=( const Context& other ) const {
    return GtdBase::operator!=(other);
}

// OVERRIDE SETTERS
/*****************************************************************************/
void
Context::setName( const std::string_view name, const bool update ) {
    GtdBase::setName(name, update);
    if ( update ) {
        auto& us = _contexts.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*uniqueId(), "name", this->name());
        }
    }
}

void
Context::setStatus( const std::string_view status, const bool update ) {
    GtdBase::setStatus(status, update);
    if ( update ) {
        auto& us = _contexts.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*uniqueId(), "status", statusStr());
        }
    }
}

void
Context::setStatus( const Status status, const bool update ) {
    GtdBase::setStatus(status, update);
    if ( update ) {
        auto& us = _contexts.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*uniqueId(), "status", statusStr());
        }
    }
}

void
Context::setParentId( const unique_id_t id, const bool update ) {
    GtdBase::setParentId(id, update);
    if ( update ) {
        auto& us = _contexts.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*uniqueId(), "parentId", *parentId());
        }
    }
}

void
Context::setNotes( const std::string_view notes, const bool update ) {
    GtdBase::setNotes(notes, update);
    if ( update ) {
        auto& us = _contexts.lock()->updateStack();
        if ( this->uniqueId() ) {
            us.push(*uniqueId(), "notes", *this->notes());
        }
    }
}
} // namespace gtd
