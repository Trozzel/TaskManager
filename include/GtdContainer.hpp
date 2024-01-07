//
// Created by George Ford on 12/16/23.
//
#ifndef GTDCONTAINER_HPP_
#define GTDCONTAINER_HPP_

#include <__ranges/filter_view.h>
#include <ranges>
#include <type_traits>

#include "UpdateStack.hpp"

namespace gtd {

template<typename Gtd_t>
class GtdContainer
{
protected:
    std::vector<Gtd_t>          _gtdItems {};
    UpdateStack&                _updateStack;

public:
   
	using gtd_category   = Gtd_t::gtd_category;
    using value_type     = std::vector<Gtd_t>::value_type;
    using iterator       = std::vector<Gtd_t>::iterator;
    using const_iterator = std::vector<Gtd_t>::const_iterator;
    using size_type      = std::vector<Gtd_t>::size_type;

	// CTORS
	/*************************************************************************/
    explicit GtdContainer() :
		_updateStack(UpdateStack::getInstance())
	{}

    ~GtdContainer() = default;


	// STATIC FUNCTIONS
	/*************************************************************************/
    [[nodiscard]] static constexpr std::string_view
    tableName( ) {
		return gtdTypeToTableName(Gtd_t::gtd_category::gtd_type);
	}

	// GETTERS
	/*************************************************************************/
    [[nodiscard]] constexpr UpdateStack&
    updateStack( ) const {
		return _updateStack;
	};

	//					BASE CONTAINER OPERATIONS
	/*************************************************************************/
    [[nodiscard]] const Gtd_t&
    operator[]( const size_t idx ) const {
		return _gtdItems[idx];
	}

    [[nodiscard]] const Gtd_t&
    at( const size_t idx ) const {
		return _gtdItems.at(idx);
	}

    [[nodiscard]] const Gtd_t&
    gtdItemByUniqueId( const unique_id_t id ) const {
		return std::ranges::find_if(_gtdItems.cbegin(), _gtdItems.cend(),
			[id](auto&& gtdItem) {
				return gtdItem.uniqueId() == id;
			});
	}

    [[nodiscard]] bool
    empty() const {
		return _gtdItems.empty();
	}

    [[nodiscard]] std::ranges::range auto&&
    getBeforeCreated( const time_point_t tp ) const {
		return _gtdItems |
				std::views::filter([tp]( auto&& gtdItem  ) {
					return gtdItem->created() < tp;
				});
	}

    [[nodiscard]] std::ranges::range auto&&
    getBeforeCreated( const Gtd_t& other ) const {
		return _gtdItems |
				std::views::filter([&other]( auto&& gtdItem) {
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
                return gtdItem.created() > gtdItem.created();
            });
	}

	/*************************************************************************/
    void
    push_back( const Gtd_t& gtdItem ) {
		_gtdItems.push_back(gtdItem);
	}

    void
    push_back( Gtd_t&& gtdItem ) {
		_gtdItems.push_back(gtdItem);
	}


	//						COMPLETABLE CONTAINER OPERATIONS
	/*************************************************************************/
    [[nodiscard]] std::ranges::range auto&&
    getWithContextId( const unique_id_t id,
			std::enable_if_t<gtd_category::completable && 
							 gtd_category::constructible, bool> = true ) const {
		return _gtdItems |
			std::views::filter([id](auto&& completable) {
					return *completable.contextId() == id;
					});
	}

    [[nodiscard]] std::ranges::range auto&&
    getAfterDeferredInclusive( const time_point_t tp,
			std::enable_if_t<gtd_category::completable &&
							 gtd_category::constructible, bool> = true ) const {
		return _gtdItems |
			std::views::filter([tp](auto&& completable) {
					return *completable.deferred() > tp;
					});
	}

    [[nodiscard]] std::ranges::range auto&&
    getBeforeDeferredInclusive( const time_point_t tp,
			std::enable_if_t<gtd_category::completable &&
							 gtd_category::constructible, bool> = true ) const {
		return _gtdItems |
			std::views::filter([tp](auto&& completable) {
					return *completable.deferred() < tp;
					});
	}

    [[nodiscard]] std::ranges::range auto&&
    getAfterDueInclusive( const time_point_t tp,
			std::enable_if_t<gtd_category::completable &&
							 gtd_category::constructible, bool> = true ) const {
		return _gtdItems |
			std::views::filter([tp](auto&& completable) {
					return *completable.due() > tp;
					});
	}

    [[nodiscard]] std::ranges::range auto&&
    getFlagged( const bool isFlagged,
			std::enable_if_t<gtd_category::completable &&
							 gtd_category::constructible, bool> = true ) const {
		return _gtdItems |
			std::views::filter([isFlagged](auto&& completable) {
					return *completable.flagged() == isFlagged;
					});
	}
	

}; // class GtdContainer

} // namespace gtd

#endif //GTDCONTAINER_HPP_
