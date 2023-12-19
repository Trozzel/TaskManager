//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_FOLDER_HPP_
#define GTD_FOLDER_HPP_

#include "GtdBase.hpp"
#include "FolderContainer.hpp"

namespace gtd {

class Folder final : public GtdBase
{
private:
    FolderContainer&  _gtdItems;

public:
    // CTORS
    /**************************************************************************/
    explicit
    Folder( FolderContainer&, std::string_view name = "" );

    ~Folder() override = default;
};

} // namespace gtd

std::ostream&
operator<<( std::ostream& out, const gtd::Folder& folder );
#endif //GTD_FOLDER_HPP_
