//
// Created by George Ford on 1/28/22.
//

#include <utility>

#include "Context.hpp"
#include "GtdBase.hpp"

namespace gtd {
// CTORS
/****************************************************************************/
Context::Context(USMgr& updateStackMgr, std::string_view name) :
	GtdBase(updateStackMgr, name) {}
}
