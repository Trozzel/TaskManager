//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_APP_CONTEXT_HPP
#define GTD_APP_CONTEXT_HPP

#include "GtdBase.hpp"
#include "ContextContainer.hpp"

namespace gtd {

class Context final : public GtdBase
{
private:
    ContextContainer&   _gtdItems;

public:
	// CTORS
	/**************************************************************************/
	explicit
    Context(ContextContainer&, std::string_view name = "");

	~Context() override = default;
};

} // namespace gtd


#endif//GTD_APP_CONTEXT_HPP
