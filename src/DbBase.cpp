//
// Created by George Ford on 12/11/23.
//

#include "DbBase.hpp"

namespace gtd {

DbBase::DbBase(const std::string_view uri) :
    _uri(uri) {}

DbBase::~DbBase() = default;

} // namespace gtd
