//
// Created by George Ford on 12/16/23.
//
#ifndef GTDBASECONTAINER_HPP_
#define GTDBASECONTAINER_HPP_

#include <vector>
#include <ranges>

#include "GtdHelper.hpp"
#include "gtd_concepts.hpp"

namespace gtd {
class Gtd;
class USMgr;

template <GtdImpl Gtd_t>
class GtdContainer
{
protected:
    std::vector<Gtd_t> _gtds{};
    USMgr&             _usMgr;

public:
    using iterator = typename std::vector<Gtd_t>::iterator;
    using const_iterator = typename std::vector<Gtd_t>::const_iterator;
    using reverse_iterator = typename std::vector<Gtd_t>::reverse_iterator;
    using const_reverse_iterator = typename std::vector<Gtd_t>::const_reverse_iterator;
    using value_type = typename std::vector<Gtd_t>::value_type;
    using refernce = typename std::vector<Gtd_t>::reference;
    using refernce_iterator = typename std::vector<Gtd_t>::reference_iterator;
    using difference_type = typename std::vector<Gtd_t>::difference_type;

    explicit
    GtdContainer( USMgr& usm ) :
        _usMgr(usm) {}

    GtdContainer( const GtdContainer& ) = delete;
    GtdContainer&
    operator=( const GtdContainer& ) = delete;

    ~GtdContainer() = default;

    [[nodiscard]]
    const USMgr&
    updateStackManager() const {
        return _usMgr;
    }

    [[nodiscard]]
    iterator
    begin() {
        return _gtds.begin();
    }

    [[nodiscard]]
    const_iterator
    cbegin() const {
        return _gtds.cbegin();
    }

    [[nodiscard]]
    iterator
    end() {
        return _gtds.end();
    }

    [[nodiscard]]
    const_iterator
    cend() const {
        return _gtds.cend();
    }

    [[nodiscard]] const Gtd_t&
    at( const size_t idx ) const {
        return _gtds.at(idx);
    }

    [[nodiscard]] Gtd_t&
    at( const size_t idx ) {
        return _gtds.at(idx);
    }

    void
    push_back( Gtd_t gtd ) {
        _gtds.push_back(std::move(gtd));
    }

    void
    push_back( const Gtd_t& gtd ) {
        _gtds.push_back(gtd);
    }

    template <typename... Args>
    void
    emplace_back( Args... args ) {
        _gtds.emplace_back(args...);
    }

    void
    erase( const Gtd_t& gtd ) {
        _gtds.erase(
            std::find(_gtds.cbegin(), _gtds.cend(), gtd));
    }

	void 
	erase( const unique_id_t id ) {
		_gtds.erase(
			std::find(*_gtds.uniqueId() == id)
				);
	}

    [[nodiscard]] const auto&&
    gtdItemByUniqueId( const unique_id_t id ) const {
        auto sameUniqueId = [id]( auto&& gtd ) {
            return gtd.uniqueId().value_or(-1) == id;
        };
        return _gtds |
                std::views::filter(sameUniqueId) |
                std::views::take(1);
    }

    [[nodiscard]] bool
    empty() const {
        return _gtds.empty();
    }

    [[nodiscard]] std::ranges::range auto&&
    getBeforeCreated( const time_point_t tp ) const {
        return _gtds |
                std::views::filter([tp]( auto&& gtd ) {
                    return gtd.created() < tp;
                });
    }

    [[nodiscard]] std::ranges::range auto&&
    getBeforeCreated( const Gtd_t& gtd ) const {
        return _gtds |
                std::views::filter([&gtd]( auto&& other ) {
                    return other.created() < gtd.created();
                });
    }

    [[nodiscard]] std::ranges::range auto&&
    getAfterCreated( const time_point_t tp ) const {
        return _gtds |
                std::views::filter([tp]( auto&& gtd ) {
                    return gtd.created() > tp;
                });
    }

    [[nodiscard]] std::ranges::range auto&&
    getAfterCreated( const Gtd_t& gtd ) const {
        return _gtds |
                std::views::filter([&gtd]( auto&& other ) {
                    return other.created() > gtd.created();
                });
    }
};
} // namespace gtd

#endif //GTDBASECONTAINER_HPP_
