//
// Created by George Ford on 1/28/22.
//

#include "Folder.hpp"

using namespace std;

namespace gtd {
// CTORS
/****************************************************************************/
Folder::Folder(string uniqueIdStr,
                 string name,
                 string statusStr,
                 string created,
                 string modified,
                 string parentIdStr) :
        GtdBase(std::move(uniqueIdStr),
                std::move(name),
                std::move(statusStr),
                std::move(created),
                std::move(modified),
                std::move(parentIdStr))
{
}

ostream& operator<<(ostream& out, const Folder& folder) {
    out << folder._uniqueId << " " << folder._name << " "
        << statusToStr(folder._status) << " "
        << fmt::format("{} ", folder._created)
        << fmt::format("{} ", folder._modified)
        << folder._parentId;

    return out;
}

}
