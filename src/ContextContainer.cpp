//
// Created by George Ford on 12/19/23.
//

#include "ContextContainer.hpp"
#include "Context.hpp"

namespace gtd {
ContextContainer::ContextContainer( USMgr& usm) :
    GtdBaseContainer(usm)
{ }

ContextContainer::~ContextContainer() = default;

std::string
ContextContainer::tableName() const {
    return "contexts";
}
} // namespace gtd