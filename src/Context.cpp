//
// Created by George Ford on 1/28/22.
//

#include <utility>

#include "Context.hpp"

using namespace std;

namespace gtd {
// CTORS
/****************************************************************************/
Context::Context(string uniqueIdStr,
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

}
