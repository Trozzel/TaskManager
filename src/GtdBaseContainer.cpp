//
// Created by George Ford on 12/16/23.
//
#include <ranges>
#include "GtdBase.hpp"
#include "GtdBaseContainer.hpp"

namespace gtd {

static_assert(IsBaseContainer<GtdContainer>);

GtdContainer::GtdBaseContainer( USMgr& usm ) :
    _usMgr(usm) {}

GtdContainer::~GtdBaseContainer() = default;

const USMgr&
GtdContainer::updateStackManager() const {
    return _usMgr;
}

auto&
GtdContainer::begin() {
    return _gtds.begin();
}

const auto&
GtdContainer::cbegin() const {
    return _gtds.cbegin();
}

auto&
GtdContainer::end() {
    return _gtds.end();
}

const auto&
GtdContainer::cend() const {
    return _gtds.cend();
}

const auto&
GtdContainer::operator[]( const size_t idx ) const {
    return _gtds[idx];
}

const auto&
GtdContainer::at( const size_t idx ) const {
    return _gtds.at(idx);
}

const auto&
GtdContainer::gtdItemByUniqueId( const unique_id_t uniqueId ) const {
    return *std::ranges::find_if(_gtds.cbegin(), _gtds.cend(),
                                 [uniqueId]( const auto&& pGtdItem ) {
                                     return *pGtdItem->uniqueId() == uniqueId;
                                 });
}

bool
GtdContainer::empty() const {
    return _gtds.empty();
}
} // namespace gtd