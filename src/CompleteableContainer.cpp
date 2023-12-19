//
// Created by George Ford on 12/17/23.
//

#include "CompleteableContainer.hpp"
#include "Completable.hpp"

namespace gtd {

CompleteableContainer::CompleteableContainer( USMgr& usm) :
    GtdBaseContainer(usm)
    {}

CompleteableContainer::~CompleteableContainer() = default;

void
CompleteableContainer::push_back( pCompletable_t pCompletable ) {
    _gtdItems.push_back(std::move(pCompletable));
}

void
CompleteableContainer::push_back( Completable* pCompletable) {
    _gtdItems.push_back(pCompletable_t(pCompletable));
}

std::ranges<pCompletable_t>
CompleteableContainer::getWithContextId(const unique_id_t id) const {
    return _gtdItems |
        std::views::filter([id](const pCompletable_t& pCompletable) {
            return *pCompletable->contextId() == id;
        });
}

std::ranges<pCompletable_t>
CompleteableContainer::getAfterDeferredInclusive(const time_point_t tp) const {
    return _gtdItems |
        std::views::filter([tp](const pCompletable_t& pComletable) {
           return *pComletable->deferred() >= tp;
        });
}

std::ranges<pCompletable_t>
CompleteableContainer::getBeforeDeferredInclusive(const time_point_t tp) const {
    return _gtdItems |
        std::views::filter([tp] (const pCompletable_t& pCompletable) {
           return *pCompletable->deferred() <= tp;
        });
}

std::ranges<pCompletable_t>
CompleteableContainer::getAfterDueInclusive(const time_point_t tp) const {
    return _gtdItems |
        std::views::filter([tp](const pCompletable_t& pCompletable) {
           return *pCompletable->due() >= tp;
        });
}

std::ranges<pCompletable_t>
CompleteableContainer::getFlagged() const {
    return _gtdItems |
        std::views::filter([](const pCompletable_t& pCompletable) {
           return pCompletable->flagged();
        });
}

}
