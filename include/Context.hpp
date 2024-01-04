//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_APP_CONTEXT_HPP
#define GTD_APP_CONTEXT_HPP

#include "ContextContainer.hpp"

namespace gtd {

class Context final : public Gtd
{
private:
    GtdContainer&   _gtds;

public:
    using gtd_category = context_tag;
	// CTORS
	/**************************************************************************/
	explicit
    Context(GtdContainer&, std::string_view name = "");

	~Context() override;

    [[nodiscard]]
    constexpr static const char*
    tableName() noexcept { return "contexts"; }
};

static_assert(IsContext<Context>);

} // namespace gtd


#endif//GTD_APP_CONTEXT_HPP
