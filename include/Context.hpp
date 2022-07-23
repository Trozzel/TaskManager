//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_APP_CONTEXT_HPP
#define GTD_APP_CONTEXT_HPP

#include <string>

#include <sqlite3.h>

#include "GtdBase.hpp"

namespace gtd {

class Context : public GtdBase {

private:

public:
	// CTORS
	/**************************************************************************/
	// DEFAULT
	Context() = default;

	// FROM SQLITE
	Context(std::string uniqueId,
			std::string name,
			std::string statusStr,
			std::string createdStr,
		    std::string modifiedStr,
			std::string parentIdStr);

	~Context() override = default;
};

} // namespace gtd


#endif//GTD_APP_CONTEXT_HPP
