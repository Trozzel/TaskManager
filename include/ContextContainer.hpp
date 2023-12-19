//
// Created by George Ford on 12/19/23.
//

#ifndef CONTEXTCONTAINER_HPP_
#define CONTEXTCONTAINER_HPP_

#include "GtdBaseContainer.hpp"

namespace gtd {

class Context;
using pContext_t = std::unique_ptr<Context>;

class ContextContainer final : public GtdBaseContainer {
private:
    std::vector<pContext_t>  _gtdItems;

public:
    explicit ContextContainer(USMgr&);
    ~ContextContainer() override;

    [[nodiscard]] std::string
    tableName() const override;
};
} //namespace gtd

#endif //CONTEXTCONTAINER_HPP_
