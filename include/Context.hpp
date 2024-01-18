//
// Created by George Ford on 1/9/24.
//

#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "GtdBase.hpp"

namespace gtd {
class Context final : public GtdBase
{
public:
    using gtd_category = context_tag;

private:
    using sp_Container = std::shared_ptr<GtdContainer<Context>>;
    using wp_Container = std::weak_ptr<GtdContainer<Context>>;
    wp_Container _contexts;

public:
    // CTORS
    /*************************************************************************/
    Context( const sp_Container&,  std::string_view name );
    Context( const Context& ) = default;
    Context( Context&& ) noexcept;

    ~Context() override = default;

    // ASSIGMENT OPERATORS
    /*************************************************************************/
    Context&
    operator=( const Context& );

    Context&
    operator=( Context&& ) noexcept;

    // COMPARISON OPERATORS
    /*************************************************************************/
    bool
    operator==( const Context& ) const;

    bool
    operator!=( const Context& ) const;

    // OVERRIDE SETTERS
    /*************************************************************************/
    void
    setName( std::string_view name, bool update ) override;

    void
    setStatus( std::string_view status, bool update ) override;

    void
    setStatus( Status status, bool update ) override;

    void
    setParentId( unique_id_t id, bool update ) override;

    void
    setNotes( std::string_view notes, bool update ) override;
};
} // namespace gtd

#endif //CONTEXT_HPP
