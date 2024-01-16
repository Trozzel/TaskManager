//
// Created by George Ford on 12/16/23.
//
#ifndef GTDCONTAINER_HPP_
#define GTDCONTAINER_HPP_

#include <ranges>
#include <algorithm>

#include "GtdHelper.hpp"
#include "Context.hpp"
#include "Project.hpp"
#include "UpdateStack.hpp"
#include "gtd_concepts.hpp"

namespace gtd {
template <typename Gtd_t>
class GtdContainer
{
protected:
    std::vector<Gtd_t> _gtdItems{};
    UpdateStack&       _updateStack;

public:
    using gtd_category = typename Gtd_t::gtd_category;
    using value_type = typename std::vector<Gtd_t>::value_type;
    using iterator = typename std::vector<Gtd_t>::iterator;
    using const_iterator = typename std::vector<Gtd_t>::const_iterator;
    using size_type = typename std::vector<Gtd_t>::size_type;

    // CTORS
    /*************************************************************************/
    explicit
    GtdContainer() :
        _updateStack(UpdateStack::getInstance()) {}

    ~GtdContainer() = default;


    // STATIC FUNCTIONS
    /*************************************************************************/
    [[nodiscard]] static constexpr std::string_view
    tableName() {
        return gtdTypeToTableName(Gtd_t::gtd_category::gtd_type);
    }

    // GETTERS
    /*************************************************************************/
    [[nodiscard]] constexpr UpdateStack&
    updateStack() const {
        return _updateStack;
    };

    //					BASE CONTAINER OPERATIONS
    /*************************************************************************/
    [[nodiscard]] const Gtd_t&
    operator[]( const size_t idx ) const {
        return _gtdItems[idx];
    }

    [[nodiscard]] Gtd_t&
    at( const size_t idx ) {
        return _gtdItems.at(idx);
    }

    [[nodiscard]] const Gtd_t&
    getItemByUniqueId( const unique_id_t id ) const {
        return std::ranges::find_if(_gtdItems.cbegin(), _gtdItems.cend(),
                                    [id]( auto&& gtdItem ) {
                                        return gtdItem.uniqueId() == id;
                                    });
    }

    [[nodiscard]] bool
    empty() const {
        return _gtdItems.empty();
    }

    [[nodiscard]] std::vector<Gtd_t>
    getByName( const std::string_view name ) {
        std::vector<Gtd_t> v;
        std::copy_if(_gtdItems.cbegin(), _gtdItems.cend(),
            std::back_inserter(v), [name](const auto& gtd) {
                return gtd.name() == name;
            });
        return v;
    }

    [[nodiscard]] std::ranges::range auto&&
    getBeforeCreated( const time_point_t tp ) const {
        return _gtdItems |
                std::views::filter([tp]( auto&& gtdItem ) {
                    return gtdItem->created() < tp;
                });
    }

    [[nodiscard]] std::ranges::range auto&&
    getBeforeCreated( const Gtd_t& other ) const {
        return _gtdItems |
                std::views::filter([&other]( auto&& gtdItem ) {
                    return other->created() < gtdItem.created();
                });
    }

    [[nodiscard]] std::ranges::range auto&&
    getAfterCreated( const time_point_t tp ) const {
        return _gtdItems |
                std::views::filter([tp]( auto&& gtdItem ) {
                    return gtdItem.created() > tp;
                });
    }

    [[nodiscard]] std::ranges::range auto&&
    getAfterCreated( const Gtd_t& other ) const {
        return _gtdItems |
                std::views::filter([&other]( auto&& gtdItem ) {
                    return gtdItem.created() > other.created();
                });
    }

    // CREATE GTD IN PLACE
    /*************************************************************************/
    Gtd_t&
    create(const std::shared_ptr<GtdContainer>& sp, const std::string_view name) {
        return _gtdItems.emplace_back(sp, name);
    }

    // VECTOR OPERATIONS
    /*************************************************************************/
    iterator
    begin() {
        return _gtdItems.begin();
    }

    const_iterator&
    cbegin() const {
        return _gtdItems.cbegin();
    }

    iterator
    end() {
        return _gtdItems.end();
    }

    const_iterator&
    cend() const {
        return _gtdItems.cend();
    }

    void
    push_back( const Gtd_t& gtdItem ) {
        _gtdItems.push_back(gtdItem);
    }

    void
    push_back( Gtd_t&& gtdItem ) {
        _gtdItems.push_back(std::move(gtdItem));
    }

    void
    erase( Gtd_t& gtdItem ) {
        std::erase(_gtdItems, gtdItem);
    }

    //						COMPLETABLE CONTAINER OPERATIONS
    /*************************************************************************/
    template <typename Completable_t = Gtd_t>
    [[nodiscard]] std::vector<Completable_t>
    getWithContextId( const unique_id_t id ) const
        requires cCompletable<Completable_t> {
        return _gtdItems |
                std::views::filter([id]( auto&& completable ) {
                    return *completable.contextId() == id;
                });
    }

    template <typename Completable_t = Gtd_t>
    [[nodiscard]] std::vector<Completable_t>
    getAfterDeferredInclusive( const time_point_t tp ) const
        requires cCompletable<Completable_t> {
        return _gtdItems |
                std::views::filter([tp]( auto&& completable ) {
                    return *completable.deferred() > tp;
                });
    }

    template <typename Completable_t = Gtd_t>
    [[nodiscard]] std::vector<Completable_t>
    getBeforeDeferredInclusive( const time_point_t tp ) const
        requires cCompletable<Completable_t> {
        return _gtdItems |
                std::views::filter([tp]( auto&& completable ) {
                    return *completable.deferred() < tp;
                });
    }

    template <typename Completable_t = Gtd_t>
    [[nodiscard]] std::vector<Completable_t>
    getAfterDueInclusive( const time_point_t tp ) const
        requires cCompletable<Completable_t> {
        return _gtdItems |
                std::views::filter([tp]( auto&& completable ) {
                    return *completable.due() > tp;
                });
    }

    template <typename Completable_t = Gtd_t>
    [[nodiscard]] std::vector<Completable_t>
    getFlagged() const
        requires cCompletable<Completable_t> {
        std::vector<Gtd_t> vec;
        std::copy_if(_gtdItems.cbegin(), _gtdItems.cend(),
                     std::back_inserter(vec), []( const auto& gtd ) {
                         return gtd.flagged() == true;
                     });
        return vec;
    }
}; // class GtdContainer
} // namespace gtd

#endif //GTDCONTAINER_HPP_