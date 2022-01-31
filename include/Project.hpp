//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_PROJECT_HPP
#define GTD_PROJECT_HPP

#include <initializer_list>
#include <memory>
#include <string>
#include <list>

#include "datetime/datetime.hpp"
#include "ProjectType.hpp"
#include "Status.hpp"
#include "Context.hpp"

namespace gtd {

class Project {
private:
    std::string _projectName{};
    std::string _notes{};
    Status      _status           { Status::Active        };
    ProjectType _projectType      { ProjectType::Parallel };
    bool        _completeWithLast { false };

    // LIST OF CONTEXTS / TAGS
    std::list<const Context*> _contexts;

    // DATES
    dt::CTime _created{};
    dt::CTime _modified{};
    dt::CTime _completed{};
    dt::CTime _dropped;
    
	// DEFERRED AND DUE DATES
	std::unique_ptr<dt::RepeatingCTime> _deferred { nullptr };
	std::unique_ptr<dt::RepeatingCTime> _due      { nullptr };

public:
	Project(std::string projectName            = "New Project",
			std::string note                   = "",
			Status      status                 = Status::Active,
			ProjectType projectType            = ProjectType::Parallel,
			std::list<const Context*> contexts = {},
			dt::RepeatingCTime* deferred       = nullptr,
			dt::RepeatingCTime* due            = nullptr
		   );

	// CTOR WITH INITIALIZER LIST
	// Make explicit to force previous to be default CTOR
	explicit Project(std::string projectName   = "New Project",
			std::string note                   = "",
			Status      status                 = Status::Active,
			ProjectType projectType            = ProjectType::Parallel,
			std::initializer_list<const Context*> contexts = {},
			dt::RepeatingCTime* deferred       = nullptr,
			dt::RepeatingCTime* due            = nullptr
		   );
	
	// GETTERS
	inline const std::string projectName() const { return _projectName; };
	inline const std::string notes()       const { return _notes; };
	inline const Status      status()      const { return _status; };

};

} // namespace gtd


#endif //GTD_PROJECT_HPP
