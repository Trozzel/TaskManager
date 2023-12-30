//
// Created by George Ford on 1/28/22.
//

#include "Folder.hpp"
#include "GtdBase.hpp"
#include "FolderContainer.hpp"

namespace gtd {
// CTORS
/****************************************************************************/
Folder::Folder(FolderContainer& gtdItems, std::string_view name) :
    GtdBase(gtdItems, name),
    _gtdItems(gtdItems)
{
    _gtdItems.push_back(this);
}

// OSTREAM
std::ostream& 
operator<<(std::ostream& out, const Folder& folder) {
    out << folder.name() << " "
        << folder.statusStr() << " "
        << fmt::format("{} ", folder.created())
        << fmt::format("{} ", folder.modified())
        << *folder.parentId();

    return out;
}
} // namespace gtd

