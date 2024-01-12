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
    using pContainer = std::shared_ptr<GtdContainer<Context>>;
    pContainer _contexts{nullptr};

public:
    // CTORS
    /*************************************************************************/
    Context( pContainer, std::string_view name );
    Context( GtdContainer<Context>*, std::string_view name );
    Context( const Context& ) = default; // !Does not add element to _contexts!
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
    setName( std::string_view name, bool update = true ) override;

    void
    setStatus( std::string_view status, bool update = true ) override;

    void
    setStatus( Status status, bool update = true ) override;

    void
    setParentId( unique_id_t id, bool update = true ) override;

    void
    setNotes( std::string_view notes, bool update = true ) override;
};
} // namespace gtd

#endif //CONTEXT_HPP
