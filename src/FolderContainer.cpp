//
// Created by George Ford on 12/19/23.
//

#include "FolderContainer.hpp"
#include "Folder.hpp"
#include "GtdBase.hpp"

namespace gtd {

FolderContainer::FolderContainer(USMgr& usm) :
    GtdBaseContainer(usm)
{}

FolderContainer::~FolderContainer() = default;

std::string
FolderContainer::tableName() const {
    return "folders";
}
} // namespace gtd