//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_FOLDER_HPP
#define GTD_FOLDER_HPP

#include <string>

#include "GtdBase.hpp"

namespace gtd {

class Folder : public GtdBase {

private:

public:
    // CTORS
    /**************************************************************************/
    // DEFAULT
    Folder() = default;

    // FROM SQLITE
    Folder(std::string uniqueId,
            std::string name,
            std::string statusStr,
            std::string createdStr,
            std::string modifiedStr,
            std::string parentIdStr);

    ~Folder() override = default;

    friend std::ostream& operator<<(std::ostream& out, const Folder& folder);
};

} // namespace gtd
#endif //GTD_FOLDER_HPP
