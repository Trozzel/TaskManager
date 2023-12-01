//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_APP_CONTEXT_HPP
#define GTD_APP_CONTEXT_HPP

#include <string>

#include "GtdBase.hpp"

namespace gtd {

class Context : public GtdBase {

private:
// The following are inherited from gtd::GtdBase
//protected:
//    LL_t         _uniqueId{-1};
//    std::string  _name;
//    Status       _status{Status::Active};
//    time_point_t _created;
//    time_point_t _modified;
//    LL_t         _parentId{-1};    // _parentId == -1 --> no parent
public:
	// CTORS
	/**************************************************************************/
	// DEFAULT
	Context() = default;

	// FROM SQLITE
	Context(const std::string& uniqueId,
			std::string_view name,
			const std::string& statusStr,
			const std::string& createdStr,
		    const std::string& modifiedStr,
			const std::string& parentIdStr);

	~Context() override = default;
};

} // namespace gtd


#endif//GTD_APP_CONTEXT_HPP
