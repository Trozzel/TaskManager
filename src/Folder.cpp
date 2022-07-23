//
// Created by George Ford on 1/28/22.
//

#include "Folder.hpp"

using namespace std;

namespace gtd {
// CTORS
/****************************************************************************/
Folder::Folder(const string & uniqueIdStr,
               const string & name,
               const string & statusStr,
               const string & created,
               const string & modified,
               const string & parentIdStr) :
        GtdBase(uniqueIdStr,
                name,
                statusStr,
                created,
                modified,
                parentIdStr)
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
