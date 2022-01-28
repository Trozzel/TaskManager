//
// Created by George Ford on 1/28/22.
//

#include "Folder.hpp"

namespace gtd {

Folder::Folder(std::string folder, Folder* parent):
    _folderName(std::move(folder)), _parent(parent)
{
}

} // namespace std