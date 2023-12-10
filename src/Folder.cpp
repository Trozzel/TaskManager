//
// Created by George Ford on 1/28/22.
//

#include "Folder.hpp"
#include "GtdBase.hpp"

namespace gtd {
// CTORS
/****************************************************************************/
Folder::Folder(USMgr& updateStackMgr, std::string_view name) : 
	GtdBase(updateStackMgr, name) {}

} // namespace gtd

std::ostream& 
operator<<(std::ostream& out, const gtd::Folder& folder) {
    out << folder.name() << " "
        << folder.statusStr() << " "
        << fmt::format("{} ", folder.created())
        << fmt::format("{} ", folder.modified())
        << *folder.parentId();

    return out;
}

