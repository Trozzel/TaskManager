//
// Created by George Ford on 1/28/22.
//

#include "Context.hpp"
#include "ContextContainer.hpp"
#include "GtdBase.hpp"

namespace gtd {
// CTORS
/****************************************************************************/
Context::Context(ContextContainer& gtdItems, std::string_view name) :
	GtdBase(gtdItems, name),
    _gtdItems(gtdItems)
{
    _gtdItems.push_back(this);
}
}
