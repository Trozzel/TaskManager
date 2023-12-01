//
// Created by George Ford on 1/28/22.
//

#include <utility>

#include "Context.hpp"

namespace gtd {
// CTORS
/****************************************************************************/
Context::Context(const std::string& uniqueIdStr,
		std::string_view name,
		const std::string& statusStr,
		const std::string& created,
		const std::string& modified,
		const std::string& parentIdStr) :
	GtdBase(uniqueIdStr,
          name,
          statusStr,
          created,
          modified,
          parentIdStr)
{
}

}
