//
// Created by George Ford on 12/19/23.
//

#ifndef CONTEXTCONTAINER_HPP_
#define CONTEXTCONTAINER_HPP_

#include "GtdBaseContainer.hpp"

namespace gtd {
class Context;
using pContext_t = std::unique_ptr<Context>;

class ContextContainer final : public GtdContainer
{
private:
    std::vector<pContext_t> _gtdItems;

public:
    using value_type = std::vector<pContext_t>::value_type;
    using iterator = std::vector<pContext_t>::iterator;
    using const_iterator = std::vector<pContext_t>::const_iterator;
    using size_type = std::vector<pContext_t>::size_type;
    using difference_type = std::vector<pContext_t>::difference_type;

    explicit
    ContextContainer( USMgr& );
    ContextContainer( const ContextContainer& ) = delete;
    ~ContextContainer() override;

    ContextContainer&
    operator=( const ContextContainer& ) = delete;

    [[nodiscard]] const std::string&
    tableName() const override;

    [[nodiscard]]
    auto
    begin() override;

    [[nodiscard]]
    auto
    cbegin() const override;

    [[nodiscard]]
    auto
    end() override;

    [[nodiscard]]
    auto
    cend() const override;

    bool
    importAllFromDb() override;
};
} //namespace gtd

#endif //CONTEXTCONTAINER_HPP_
