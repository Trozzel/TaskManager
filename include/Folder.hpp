//
// Created by George Ford on 1/9/24.
//

#ifndef FOLDER_HPP
#define FOLDER_HPP

#include "GtdBase.hpp"
#include <optional>

namespace gtd {

template<typename Gtd_t>
class GtdContainer;

class Folder final : public GtdBase
{
public:
    using gtd_category = folder_tag;

	// STATIC FUNCTIONS
	static constexpr const char*
	tableName() {
		return "folders";
	}
private:
    using sp_Container = std::shared_ptr<GtdContainer<Folder>>;
    using wp_Container = std::weak_ptr<GtdContainer<Folder>>;
    wp_Container _folders;

public:
    // CTORS
    /*************************************************************************/
    explicit Folder( const sp_Container&, std::string_view name = "" );
    explicit Folder( wp_Container, std::string_view name = "" );
    Folder( const Folder& ) = default; // !Does not add element to _folders!

    ~Folder() override = default;

    // ASSIGMENT OPERATORS
    /*************************************************************************/
    Folder&
    operator=( const Folder& );

    // COMPARISON OPERATORS
    /*************************************************************************/
    bool
    operator==( const Folder& ) const;

    bool
    operator!=( const Folder& ) const;

	// GETTERS
	/*************************************************************************/
	wp_Container
	container();

	const wp_Container
	container() const;

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
    setParentId( std::optional<unique_id_t> id, bool update ) override;

    void
    setNotes( std::string_view notes, bool update ) override;

	// CONTEXT SETTERS
	/*************************************************************************/
	void
	setContainer( sp_Container& container );
	
	void
	setContainer( wp_Container container );
	

};
} // namespace gtd

#endif //FOLDER_HPP
