//
// Created by George Ford on 12/14/23.
//

#ifndef UPDATESTACK_HPP_
#define UPDATESTACK_HPP_

#include "GtdHelper.hpp"
#include "GtdBaseContainer.hpp"

namespace gtd {
using ColName_t = std::string_view;
using ValueStr_t = std::string;
using stack_elem_t = std::tuple<unique_id_t, ColName_t, ValueStr_t>;

// CLASS UPDATE STACK
/*****************************************************************************/
class UpdateStack
{
protected:
    std::stack<stack_elem_t> _dbUpdateStack;

public:
    UpdateStack( );

    ~UpdateStack();

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
    stack_elem_t&
    top();

    std::string
    compose( const GtdBaseContainer& );

}; // class UpdateStack

// CLASS UpdateStackManager
/// \brief SINGLETON PATTERN use getInstance to get reference to the single
/// instance
/// Since USMgr handles a unique pointer, Single pattern facilitates handling
/// the allocated object within the unique pointer
/*****************************************************************************/
class USMgr
{
    // unique_ptr deleter that returns resource to the UpdateStackMgr object
    struct USPtrDeleter
    {
        USMgr& _usMgr;
        explicit
        USPtrDeleter( USMgr& usm );
        void
        operator()( UpdateStack* updateStackPtr ) const;
    };

private:
    using USPtr_t = std::unique_ptr<UpdateStack, USPtrDeleter>;
    USPtr_t _pUpdateStack;

    USMgr( const USMgr& );
    USMgr&
    operator=( const USMgr& );
public:
    // CTORS
    /*************************************************************************/
    /// \brief Default CTOR to allow for lazy construction.
    /// \warn USPtr_t will be set to nullptr
    USMgr( );

    /// Since UpdateStackManager handles the resource to the UpdateStack
    /// object, UpdateStackManager will destroy the object
    ~USMgr() {
        /// _pUpdateStack should never be a nullptr at time of
        /// UpdateStackManager destructor, but for sanity check...
        if ( _pUpdateStack ) {
            delete _pUpdateStack.release();
        }
    }

    [[nodiscard]]
    const USPtr_t&
    getUpdateStack() const;

};

} // namespace gtd

#endif //UPDATESTACK_HPP_
