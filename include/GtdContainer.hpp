//
// Created by George Ford on 12/16/23.
//
#ifndef GTDCONTAINER_HPP_
#define GTDCONTAINER_HPP_

#include <__ranges/concepts.h>
#include <__ranges/filter_view.h>
#include <_ctype.h>
#include <functional>
#include <memory>
#include <ranges>
#include <algorithm>

#include "GtdHelper.hpp"
#include "Context.hpp"
#include "Folder.hpp"
#include "GtdSqlite.hpp"
#include "Task.hpp"
#include "Project.hpp"
#include "UpdateStack.hpp"
#include "fmt/base.h"
#include "gtd_concepts.hpp"

namespace gtd {
template <typename Gtd_t> // TODO: why not able to use concept, cGtd?
class GtdContainer
{
protected:
    std::vector<Gtd_t>		  _gtdItems{};
    UpdateStack<Gtd_t>&       _updateStack;

public:
    using gtd_category    = typename Gtd_t::gtd_category;
    using value_type      = typename std::vector<Gtd_t>::value_type;
    using iterator        = typename std::vector<Gtd_t>::iterator;
    using const_iterator  = typename std::vector<Gtd_t>::const_iterator;
    using size_type       = typename std::vector<Gtd_t>::size_type;
    using reference       = typename std::vector<Gtd_t>::reference;
    using const_reference = typename std::vector<Gtd_t>::const_reference;

    // CTORS
    /*************************************************************************/
    explicit
    GtdContainer() :
        _updateStack(UpdateStack<Gtd_t>::getInstance()) {}

	GtdContainer( const GtdContainer& ) = delete;
	GtdContainer& operator=( const GtdContainer& ) = delete;

    ~GtdContainer() = default;

    // STATIC FUNCTIONS
    /*************************************************************************/
    [[nodiscard]] static constexpr std::string
    tableName() {
        return gtdTypeToTableName(Gtd_t::gtd_category::gtd_type);
    }

	// INITIATE CONTAINER FROM DATABASE
    static std::shared_ptr<GtdContainer>&
    initFromDb() 
    {
		static bool firstCall = true;
		static auto cont = std::make_shared<GtdContainer>();
		if ( firstCall ) {
			loadFromDb(cont);
			firstCall = false;
		}
		return cont;
    }
	
    // GETTERS
    /*************************************************************************/
    [[nodiscard]] constexpr UpdateStack<Gtd_t>&
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
        assert(idx < _gtdItems.size());
        return _gtdItems.at(idx);
    }

    [[nodiscard]] size_type
    size() const {
        return _gtdItems.size();
    }

    [[nodiscard]] bool
    empty() const {
        return _gtdItems.empty();
    }

	size_type
    cap() const {
        return _gtdItems.capacity();
    }

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

    reference
    back() {
        return _gtdItems.back();
    }

    const_reference
    back() const {
        return _gtdItems.back();
    }

    void
    removeItem( Gtd_t& gtdItem ) {
		// 1. REMOVE FROM DATABASE
		auto numRemoved = removeRecord(gtdItem);
		// 2. REMOVE FROM CONTAINER
		if (numRemoved > 0) /* should be == 1 */{
			_gtdItems.erase(
				std::find(_gtdItems.begin(), _gtdItems.end(), gtdItem),
				_gtdItems.end());
		}
    }

	// CONTAINER SEARCH OPERATIONS
	/*************************************************************************/
    [[nodiscard]] std::vector<Gtd_t>
    getByName( std::string name, bool ignoreCase = false ) {
		std::string scopeName = std::move(name);

		// 1. INITIALIZE COMPARITOR
		std::function<bool(const Gtd_t&)> comp = [&scopeName](const Gtd_t& other) {
			return std::string_view(scopeName) == other.name();
		};
		// 2. SET ALL STRINGS tolower IF `ignoreCase`
		if(ignoreCase) {
			// 1. Set name from passed object to lower
			std::transform(scopeName.begin(), scopeName.end(), scopeName.begin(),
					::tolower);
			// 2. Copy name from container and set copy to lower
			comp = [&scopeName] (const Gtd_t& other) {
				std::string tmpName { other.name() }; // Implicit conversion from string_view to string
				std::transform(tmpName.begin(), tmpName.end(), tmpName.begin(), ::tolower);
				return tmpName == scopeName;
			};
		}
        std::vector<Gtd_t> v;
        std::copy_if(_gtdItems.cbegin(), _gtdItems.cend(), std::back_inserter(v), comp);
        return v;
    }

    [[nodiscard]] const auto&
    getByUniqueId( const unique_id_t id ) const {
        return std::ranges::find_if(_gtdItems.cbegin(), _gtdItems.cend(),
				[id]( auto&& gtdItem ) {
					return gtdItem.uniqueId() == id;
				});
    }

    [[nodiscard]] std::ranges::range auto
    getBeforeCreated( const time_point_t tp ) const {
		return _gtdItems |
			std::views::filter([tp](auto&& gtdItem) {
					return gtdItem.created() < tp;
					});
    }

    [[nodiscard]] std::vector<Gtd_t>
    getBeforeCreated( const std::string_view createdStr ) const {
		auto created = strToTimePoint(createdStr);
		return getBeforeCreated(created);
    }

    [[nodiscard]] std::ranges::range auto
    getAfterCreated( const time_point_t tp ) const {
		return _gtdItems |
			std::views::filter([tp](auto&& gtdItem) {
				return gtdItem.created() > tp;
			});
    }

    [[nodiscard]] std::ranges::range auto
    getAfterCreated( const std::string_view createdStr ) const {
		auto created = strToTimePoint(createdStr);
		return getAfterCreated(created);
    }

    // ADD GtdItem TO CONTAINER
    /*************************************************************************/
    reference
    create( const std::shared_ptr<GtdContainer>& sp, const std::string_view name ) {
        _gtdItems.emplace_back(sp, name);
        return _gtdItems.back();
    }

    const_reference
    create( const std::shared_ptr<GtdContainer>& sp, const std::string_view name ) const {
        _gtdItems.emplace_back(sp, name);
        return _gtdItems.back();
    }

	void
	attach( Gtd_t& gtdItem ) {
		assert(!_gtdItems.empty());
		gtdItem.setContainer(_gtdItems.at(0).container());
		if(!gtdItem.uniqueId() /*optional<unique_id_t>*/)  {
			// insertRecord inserts into database and returns uniqueId
			gtdItem.setUniqueId(insertRecord(gtdItem));
			_gtdItems.push_back(gtdItem);
		}
	}

	// SEND UPDATES TO DATABASE
	size_t
	updateDb() {
		return _updateStack.update();
	}
    
    //						COMPLETABLE CONTAINER OPERATIONS
    /*************************************************************************/
    template <typename Completable_t = Gtd_t>
    [[nodiscard]] std::ranges::range auto
    getWithContextId( const unique_id_t id ) const
        requires cCompletable<Completable_t> 
	{
        return _gtdItems |
                std::views::filter([id]( auto&& completable ) {
                    return *completable.contextId() == id;
                });
    }

    template <typename Completable_t = Gtd_t>
    [[nodiscard]] std::ranges::range auto
    getWithContext( const Context& context ) const
        requires cCompletable<Completable_t> 
	{
        return _gtdItems |
                std::views::filter([&context]( auto&& completable ) {
                    return *completable.contextId() == *context.uniqueId();
                });
    }

    template <typename Completable_t = Gtd_t>
    [[nodiscard]] std::ranges::range auto
    getAfterDeferredInclusive( const time_point_t tp ) const
        requires cCompletable<Completable_t> 
	{
        return _gtdItems |
                std::views::filter([tp]( auto&& completable ) {
                    return *completable.deferred() > tp;
                });
    }

    template <typename Completable_t = Gtd_t>
    [[nodiscard]] std::vector<Completable_t>
    getAfterDeferredInclusive( const std::string_view tpStr ) const
        requires cCompletable<Completable_t> 
	{
		auto tp = strToTimePoint(tpStr);
		getAfterDeferredInclusive(tp);
    }

    template <typename Completable_t = Gtd_t>
    [[nodiscard]] std::ranges::range auto
    getBeforeDeferredInclusive( const time_point_t tp ) const
        requires cCompletable<Completable_t> 
	{
        return _gtdItems |
                std::views::filter([tp]( auto&& completable ) {
                    return *completable.deferred() < tp;
                });
    }

    template <typename Completable_t = Gtd_t>
    [[nodiscard]] std::vector<Completable_t>
    getAfterDueInclusive( const time_point_t tp ) const
        requires cCompletable<Completable_t> 
	{
        return _gtdItems |
                std::views::filter([tp]( auto&& completable ) {
                    return *completable.due() > tp;
                });
    }

    template <typename Completable_t = Gtd_t>
    [[nodiscard]] std::vector<Completable_t>
    getFlagged() const 
		requires cCompletable<Completable_t> 
	{
		return _gtdItems |
			std::views::filter([](auto&& gtdItem){
					return gtdItem.flagged() == true;
					});
    }

	// TASK CONTAINER OPERATIONS
	template<typename Task_t = Gtd_t>
	[[nodiscard]] std::vector<Task_t>
	getTasksByProject(const Project& project) 
		requires cTask<Task_t>
	{
		return _gtdItems |
			std::views::filter([&project](auto&& task) { 
					return *task.projectId() == *project.uniqueId();
					});
	}

}; // class GtdContainer

} // namespace gtd

#endif //GTDCONTAINER_HPP_
