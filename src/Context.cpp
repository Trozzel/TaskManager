//
// Created by George Ford on 1/28/22.
//

#include "Context.hpp"
#include "ContextContainer.hpp"
#include "GtdBase.hpp"

namespace gtd {
// CTORS
/****************************************************************************/
Context::Context(GtdContainer& gtdItems, std::string_view name) :
	Gtd(gtdItems, name),
    _gtds(gtdItems)
{
    _gtds.push_back(this);
}

} // namespace gtd
