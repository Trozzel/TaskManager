//
// Created by George Ford on 12/16/23.
//
#include <ranges>
#include "GtdBase.hpp"
//#include "GtdBaseContainer.hpp"
#include "UpdateStack.hpp"

namespace gtd {
GtdContainer::GtdContainer(UpdateStack& updateStack) :
	_updateStack(UpdateStack::getInstance())
{}

GtdContainer::~GtdContainer() = default;

const USMgr&
GtdContainer::updateStack() const {
    return _usMgr;
}

const pGtdBase_t&
GtdContainer::operator[]( const size_t idx ) const {
    return _gtdItems[idx];
}

const pGtdBase_t&
GtdContainer::at( const size_t idx ) const {
    return _gtdItems.at(idx);
}

void
GtdContainer::push_back( GtdBase* pGtdBase) {
    _gtdItems.push_back(pGtdBase_t(pGtdBase));
}

void
GtdContainer::push_back(pGtdBase_t pGtdBase) {
    _gtdItems.push_back(std::move(pGtdBase));
}

bool
GtdContainer::empty() const {
    return _gtdItems.empty();
}

const pGtdBase_t&
GtdContainer::gtdItemByUniqueId( const unique_id_t uniqueId ) const {
    return *std::ranges::find_if(_gtdItems.cbegin(), _gtdItems.cend(),
        [uniqueId](const pGtdBase_t& pGtdItem) {
            return *pGtdItem->uniqueId() == uniqueId;
        });
}

std::ranges<pGtdBase_t>
GtdContainer::getBeforeCreated( const time_point_t tp ) const {
    return _gtdItems |
            std::views::filter([tp]( const pGtdBase_t& pGtdItem  ) {
                return pGtdItem->created() < tp;
            });
}

std::ranges<pGtdBase_t>
GtdContainer::getBeforeCreated( const pGtdBase_t& other ) const {
    return _gtdItems |
            std::views::filter([&other]( const auto& pGtdItem ) {
                return other->created() < pGtdItem->created();
            });
}

std::ranges<pGtdBase_t>
GtdContainer::getAfterCreated( const time_point_t tp ) const {
    return _gtdItems |
            std::views::filter([tp]( const pGtdBase_t& pGtdItem ) {
                return pGtdItem->created() > tp;
            });
}

std::ranges<pGtdBase_t>
GtdContainer::getAfterCreated( const pGtdBase_t& other ) const {
    return _gtdItems |
            std::views::filter([&other]( const pGtdBase_t& pGtdItem ) {
                return other->created() > pGtdItem->created();
            });
}
} // namespace  gtd
