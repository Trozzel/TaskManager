//
// Created by George Ford on 12/14/23.
//

#ifndef UPDATESTACK_HPP_
#define UPDATESTACK_HPP_

#include <stack>

#include "GtdHelper.hpp"

namespace gtd {
using ColName_t = std::string;
using ValueStr_t = std::string;
using id_col_val_t = std::tuple<unique_id_t, ColName_t, ValueStr_t>;

// CLASS UPDATE STACK
/*****************************************************************************/
class UpdateStack
{
protected:
    std::stack<id_col_val_t> _dbUpdateStack;

public:
    using value_type = std::stack<id_col_val_t>::value_type;
    using reference = std::stack<id_col_val_t>::reference;
    using const_reference = std::stack<id_col_val_t>::const_reference;

    UpdateStack() = default;

    ~UpdateStack() = default;

    UpdateStack( const UpdateStack& ) = delete;

    UpdateStack&
    operator=( const UpdateStack& ) = delete;

    static UpdateStack&
    getInstance() {
        static UpdateStack us;
        return us;
    }

    void
    clear();

    template <typename Int>
    void
    push( unique_id_t uniqueId, std::string_view colName, Int value )
        requires std::is_integral_v<Int> {
        _dbUpdateStack.emplace(uniqueId, colName, std::to_string(value));
    }

    template <typename String>
    void
    push( unique_id_t uniqueId, std::string_view colName, String value )
        requires std::convertible_to<String, std::string> || std::constructible_from<String, const char*> {
        _dbUpdateStack.emplace(uniqueId, colName, value);
    }

    void
    push( unique_id_t uniqueId, std::string_view colName, bool );

    [[nodiscard]]
    constexpr size_t
    size() const {
        return _dbUpdateStack.size();
    }

    [[nodiscard]]
    constexpr unique_id_t
    topUniqueId() const {
        return std::get<0>(_dbUpdateStack.top());
    }

    [[nodiscard]]
    constexpr ColName_t
    topColName() const {
        return std::get<1>(_dbUpdateStack.top());
    }

    [[nodiscard]]
    constexpr const ValueStr_t&
    topValueStr() const {
        return std::get<2>(_dbUpdateStack.top());
    }

    void
    pop();

    [[nodiscard]]
    const_reference
    top() const;

    //std::string
    //compose( const GtdContainer<>& );
}; // class UpdateStack
} // namespace gtd

#endif //UPDATESTACK_HPP_
