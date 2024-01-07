//
// Created by George Ford on 12/14/23.
//

#ifndef UPDATESTACK_HPP_
#define UPDATESTACK_HPP_

#include <stack>

#include "GtdHelper.hpp"

namespace gtd {

using ColName_t = std::string_view;
using ValueStr_t = std::string;
using id_colname_t = std::tuple<unique_id_t, ColName_t, ValueStr_t>;

// CLASS UPDATE STACK
/*****************************************************************************/
/**
 * Singleton that is shared by all GtdContainers
 * @brief composes UPDATE queries to be sent to the database
 */ 
class UpdateStack
{
protected:
    std::stack<id_colname_t> _dbUpdateStack;

public:
    UpdateStack( );

    ~UpdateStack();

	UpdateStack(const UpdateStack&) = delete;

	UpdateStack&
	operator=(const UpdateStack&) = delete;

	static UpdateStack&
		getInstance() {
			static UpdateStack us;
			return us;
		}

    void
    clear();

    void
    push (unique_id_t uniqueId, std::string_view colName, unique_id_t);

    void
    push (unique_id_t uniqueId, std::string_view colName, std::string_view);

    void
    push (unique_id_t uniqueId, std::string_view colName, std::string);

    void
    push (unique_id_t uniqueId, std::string_view colName, bool);

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
    id_colname_t&
    top();

    //std::string
    //compose( const GtdContainer<>& );

}; // class UpdateStack


} // namespace gtd

#endif //UPDATESTACK_HPP_
