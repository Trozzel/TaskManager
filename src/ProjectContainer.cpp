//
// Created by George Ford on 12/19/23.
//

#include "ProjectContainer.hpp"

namespace gtd {
ProjectContainer::ProjectContainer( USMgr& usm ) :
    CompleteableContainer(usm) {}

ProjectContainer::ProjectContainer( const ProjectContainer& other ) :
    CompleteableContainer(other),
    _gtdItems(other._gtdItems)
{
}

ProjectContainer::~ProjectContainer() = default;

ProjectContainer&
ProjectContainer::operator=( const ProjectContainer& other ) {
    if ( this != &other ) {
        _gtdItems = other._gtdItems;
        _usMgr    = other._usMgr;
    }
    return *this;
}

auto
ProjectContainer::begin() {
    return _gtdItems.begin();
}

auto
ProjectContainer::cbegin() const {
    return _gtdItems.cbegin();
}

auto
ProjectContainer::end() {
    return _gtdItems.end();
}

auto
ProjectContainer::cend() const {
    return _gtdItems.cend();
}


const std::string&
ProjectContainer::tableName() const {
    static const std::string table = "projects";
    return table;
}
} // namespace gtd
