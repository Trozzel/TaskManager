//
// Created by George Ford on 12/19/23.
//

#include "FolderContainer.hpp"
#include "GtdBase.hpp"

namespace gtd {

FolderContainer::FolderContainer( USMgr& usm ) :
    GtdBaseContainer(usm)
{
}

FolderContainer::~FolderContainer() = default;

const std::string&
FolderContainer::tableName() const {
    static const std::string table = "folders";
    return table;
}

auto
FolderContainer::begin() {
    return _gtdItems.begin();
}

auto
FolderContainer::cbegin() const {
    return _gtdItems.cbegin();
}

auto
FolderContainer::end() {
    return _gtdItems.end();
}

auto
FolderContainer::cend() const {
    return _gtdItems.cend();
}
} // namespace gtd
