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

/**
 * @brief Represents a Project in GTD program
 * @author George Ford
 *
 * Represents the Projects from SQLite database in memory
 */
class Project {
private:
    std::string _projectName{};
    std::string _notes{};
    Status      _status           { Status::Active        };
    ProjectType _projectType      { ProjectType::Parallel };
    bool        _completeWithLast { false };

    // LIST OF CONTEXTS (TAGS)
    std::list<const Context*> _contexts;

    // DATES
    std::unique_ptr<dt::CTime> _created   { nullptr };
    std::unique_ptr<dt::CTime> _modified  { nullptr };
    std::unique_ptr<dt::CTime> _completed { nullptr };
    std::unique_ptr<dt::CTime> _dropped   { nullptr };
    
	// DEFERRED AND DUE DATES
	std::unique_ptr<dt::RepeatingCTime> _deferred { nullptr };
	std::unique_ptr<dt::RepeatingCTime> _due      { nullptr };

public:
    /**
     * Class providing functionality for manipulating projects from SQLite
     * database.
     * This is called for default instantiation
     * @param projectName
     * @param note
     * @param status
     * @param projectType
     * @param contexts
     * @param deferred
     * @param due
     */
	Project(std::string projectName            = "New Project",
			std::string note                   = "",
			Status      status                 = Status::Active,
			ProjectType projectType            = ProjectType::Parallel,
			std::list<const Context*> contexts = {},
			dt::RepeatingCTime* deferred       = nullptr,
			dt::RepeatingCTime* due            = nullptr
		   );

	/**
	 * Class with initilizer_list of Contexts for instantiation.
	 * Made explicit to force to not be the default CTOR
	 * @param projectName
	 * @param note
	 * @param status
	 * @param projectType
	 * @param contexts
	 * @param deferred
	 * @param due
	 */
	explicit Project(std::string projectName   = "New Project",
			std::string note                   = "",
			Status      status                 = Status::Active,
			ProjectType projectType            = ProjectType::Parallel,
			std::initializer_list<const Context*> contexts = {},
			dt::RepeatingCTime* deferred       = nullptr,
			dt::RepeatingCTime* due            = nullptr
		   );

    /********************************* GETTERS ********************************/
    /**
     * @return string containing project name
     */
	inline const std::string projectName() const { return _projectName; };

    /**
     * @return string containing project notes
     */
	inline const std::string notes() const { return _notes; };

    /**
     * @return status of project
     */
	inline const Status status() const { return _status; };

    /**
     * @return String representing the Status
     */
     const std::string statusString() const;

     /**
      *
      * @return String representing the project type
      */
     const std::string projectTypeString() const;

     /**
      * @return Complete Project when last task completed status
      */
     inline const bool completeWithLast() const { return _completeWithLast; }

     /**
      * @return List of contexts associated with project
      */
     const std::list<const Context*> const contexts();

     /**
      * @return Created datetime object
      */
     inline const dt::CTime created() const { return _created; }

     /**
      * @return Modified datetime object
      */
     inline const dt::CTime modified() const { return _modified; }

     /**
      * @return Completed datetime object
      */
    inline const dt::CTime completed() const { return _completed; }

    /**
     * @return Dropped datetime object
     */
    inline const dt::CTime dropped() const { return _dropped; }

    /**
     * @return Deferred repeating CTime object
     */
    inline std::unique_ptr<dt::RepeatingCTime> deferred() const {
        return _deferred;
    }

    /**
     * @return Due repeating CTime object
     */
    inline std::unique_ptr<dt::RepeatingCTime> due() const {
        return _due;
    }

    /********************************* SETTERS ********************************/
    void setProjectName(const std::string& projectName);
    void setNotes(const std::string& notes);
    inline void setStatus(Status status) { _status = status; }
    inline void setProjectType(ProjectType projectType) {
        _projectType = projectType;
    }
    inline void setCompleteWithLast(bool completeWithLast) {
        _completeWithLast = completeWithLast;
    }

    /********************************* SETTERS ********************************/
     void setProjectName(const std::string& projectName);
     void setNotes(const std::string& notes);
     inline void setStatus(Status status) { _status = status; }
     inline void setProjectType(ProjectType projectType) {
         _projectType = projectType;
     }
     inline void setCompleteWithLast(bool completeWithLast) {
         _completeWithLast = completeWithLast;
     }
     void setContexts(std::initializer_list<const Context*> contexts);
     void setContexts(std::list<const Context*> contexts);
     inline void addContext(const Context* context) {
         _contexts.push_back(context);
     }
     const Context* removeContext(const Context* context);
     inline void updateModified() {  _modified = dt::CTime{}; }
     void markAsComplete(); // CHANGE STATUS AND COMPLETED DATE
};

} // namespace gtd


#endif //GTD_PROJECT_HPP
