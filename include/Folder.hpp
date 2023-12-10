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
    Folder(USMgr&, std::string_view name = "");

    ~Folder() override = default;

	// GETTERS
	/*************************************************************************/
};

} // namespace gtd

std::ostream& 
operator<<(std::ostream& out, const gtd::Folder& folder);
#endif //GTD_FOLDER_HPP
