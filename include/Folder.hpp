//
// Created by George Ford on 1/9/24.
//

#ifndef FOLDER_HPP
#define FOLDER_HPP

#include "GtdBase.hpp"

namespace gtd {
class Folder final : public GtdBase
{
public:
    using gtd_category = folder_tag;

private:
    using pContainer = std::shared_ptr<GtdContainer<Folder>>;
    pContainer _folders{nullptr};

public:
    // CTORS
    /*************************************************************************/
    Folder( pContainer, std::string_view name );
    Folder( GtdContainer<Folder>*, std::string_view name );
    Folder( const Folder& ) = default; // !Does not add element to _folders!
    Folder( Folder&& ) noexcept;

    ~Folder() override = default;

    // ASSIGMENT OPERATORS
    /*************************************************************************/
    Folder&
    operator=( const Folder& );

    Folder&
    operator=( Folder&& ) noexcept;

    // COMPARISON OPERATORS
    /*************************************************************************/
    bool
    operator==( const Folder& ) const;

    bool
    operator!=( const Folder& ) const;

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

#endif //FOLDER_HPP
