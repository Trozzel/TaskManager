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
Context::Context( pContainer contexts, const std::string_view name ) :
    GtdBase(name),
    _contexts(std::move(contexts)) {
    //_contexts->push_back(*this);
}

Context::Context( GtdContainer<Context>* contexts, const std::string_view name ) :
    GtdBase(name),
    _contexts(contexts) {
    //_contexts->push_back(*this);
}

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
        _contexts = other._contexts; // Not necessary since shouldn't be +1 Context Container
    }
    return *this;
}

Context&
Context::operator=( Context&& other ) noexcept {
    if ( this != &other ) {
        GtdBase::operator=(std::move(other));
        _contexts->erase(*this);
        _contexts = std::move(other._contexts);
        _contexts->push_back(*this);
    }
    return *this;
}

// COMPARISON OPERATORS
/*************************************************************************/
bool
Context::operator==( const Context& other ) const {
    return GtdBase::operator==(other) && _contexts == other._contexts;
}

bool
Context::operator!=( const Context& other ) const {
    return GtdBase::operator!=(other) && _contexts != other._contexts;
}

// OVERRIDE SETTERS
/*****************************************************************************/
void
Context::setName( const std::string_view name, const bool update ) {
    GtdBase::setName(name, update);
    if ( update ) {
        auto& us = _contexts->updateStack();
        if ( this->uniqueId() ) {
            us.push(*uniqueId(), "name", this->name());
        }
    }
}

void
Context::setStatus( const std::string_view status, const bool update ) {
    GtdBase::setStatus(status, update);
    if ( update ) {
        auto& us = _contexts->updateStack();
        if ( this->uniqueId() ) {
            us.push(*uniqueId(), "status", statusStr());
        }
    }
}

void
Context::setStatus( const Status status, const bool update ) {
    GtdBase::setStatus(status, update);
    if ( update ) {
        auto& us = _contexts->updateStack();
        if ( this->uniqueId() ) {
            us.push(*uniqueId(), "status", statusStr());
        }
    }
}

void
Context::setParentId( const unique_id_t id, const bool update ) {
    GtdBase::setParentId(id, update);
    if ( update ) {
        auto& us = _contexts->updateStack();
        if ( this->uniqueId() ) {
            us.push(*uniqueId(), "parentId", *parentId());
        }
    }
}

void
Context::setNotes( const std::string_view notes, const bool update ) {
    GtdBase::setNotes(notes, update);
    if ( update ) {
        auto& us = _contexts->updateStack();
        if ( this->uniqueId() ) {
            us.push(*uniqueId(), "notes", *this->notes());
        }
    }
}
} // namespace gtd
