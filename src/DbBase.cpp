//
// Created by George Ford on 12/11/23.
//

#include "DbBase.hpp"

DbBase::DbBase(std::string_view uri) :
    _uri(uri) {}

DbBase::~DbBase() = default;
