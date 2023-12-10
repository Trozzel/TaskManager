#include <optional>
#include "GtdBase.hpp"

namespace gtd {
// CTORS
/*****************************************************************************/
GtdBase::GtdBase(USMgr& updateStackMgr, std::string_view name) :
	_updateStackMgr(updateStackMgr),
	_name(name){}

// DTOR
// Must define destructor for inheriting classes
GtdBase::~GtdBase() = default;

// GETTERS
/*****************************************************************************/
std::optional<std::string_view>
GtdBase::notes() const {
	if(_o_notes) {
		return *_o_notes;
	}
	return std::nullopt;
}

// SETTERS
/*****************************************************************************/

/// \note implementation is handled in derived classes to write to DB upon 
/// update
void 
GtdBase::setName(std::string_view name, bool update) {
	_name = name;
	if(update) {
		auto pUpdateStack =_updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "name");
	}
}

/// \note implementation is handled in derived classes to write to DB upon 
/// update
void 
GtdBase::setStatus(std::string_view statusStr, bool update) {
	_status = strToStatus(statusStr);
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "status");
	}
}

/// \note implementation is handled in derived classes to write to DB upon 
/// update
void 
GtdBase::setStatus(Status status, bool update) noexcept {
	_status = status;
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "status");
	}
}

/// \note implementation is handled in derived classes to write to DB upon 
/// update
void 
GtdBase::setCreated(std::string_view created, bool update) {
	_created = strToTimePoint(created);
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "created");
	}
}

/// \note implementation is handled in derived classes to write to DB upon 
/// update
void 
GtdBase::setCreated(time_point_t tp, bool update) noexcept {
	_created = tp;
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "created");
	}
}

/// \note implementation is handled in derived classes to write to DB upon 
/// update
void 
GtdBase::setModified(std::string_view modified, bool update) {
	_modified = strToTimePoint(modified);
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "modified");
	}
}

/// \note implementation is handled in derived classes to write to DB upon 
/// update
void 
GtdBase::setModified(time_point_t tp, bool update) noexcept {
	_modified = tp;
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "modified");
	}
}

/// \note implementation is handled in derived classes to write to DB upon 
/// update
void 
GtdBase::setParentId(unique_id_t id, bool update) {
	_o_parentId = id;
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "parentId");
	}
}

/// \note implementation is handled in derived classes to write to DB upon 
/// update
void
GtdBase::GtdBase::setNotes(std::string_view notes, bool update) {
	_o_notes = notes;
	if(update) {
		auto pUpdateStack = _updateStackMgr.getUpdateStack();
		pUpdateStack->push(*this, "notes");
	}
}

// PULL OPERATOR FOR OSTREAM
std::ostream&
operator<<(std::ostream &out, const GtdBase &base) {
	out << *base.uniqueId() << " " << base.name() << " "
		<< base.statusStr() << " "
		<< base.createdStr() << " "
		<< base.modifiedStr() << " "
		<< *base.parentId();

	return out;
}
} // namespace gtd
