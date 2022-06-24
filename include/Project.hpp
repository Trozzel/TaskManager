//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_PROJECT_HPP
#define GTD_PROJECT_HPP

#include <initializer_list>
#include <memory>
#include <string>
#include <list>

#include "ProjectType.hpp"
#include "Status.hpp"
#include "Context.hpp"
#include "Folder.hpp"

// Forward declaration of Task to avoid header recursion
class Task;

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
    const Folder* _folder { nullptr };
    Status _status { Status::Active        };
    ProjectType _projectType { ProjectType::Parallel };
    bool _completeWithLast { false };

    /**
     * List of Contexts
     */
    std::list<const Context*> _contexts{};

    /**
     * List of Tasks
     */
    std::list<const Task*> _tasks{};

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
	Project(std::string projectName = "New Project",
			std::string notes = "",
            const Folder* folder = nullptr,
			Status status = Status::Active,
			ProjectType projectType = ProjectType::Parallel,
			std::list<const Context*> contexts = {},
			std::list<const Task*> tasks = {},
			dt::RepeatingCTime*  = nullptr,
			dt::RepeatingCTime* due = nullptr
		   );

    /********************************* GETTERS ********************************/
    /**
     * @return string containing project name
     */
    inline std::string projectName() const {
        return _projectName;
    }

    /**
     * @return string containing project notes
     */
    inline const std::string notes() const { return _notes; }

    /**
     * @return Folder* to the containing folder
     */
    inline const Folder* folder() const { return _folder; }

    /**
    * @return string containing folder name
    */
    inline std::string folderName() const {
        return _folder->folderName();
    }

    /**
     * @return status of project
     */
    inline const Status status() const { return _status; }

     /**
     * @return String representing the Status
     */
     std::string statusString() const;

     /**
      * @return ProjectType
      */
     inline const ProjectType projectType() const { return _projectType; }

     /**
      *
      * @return String representing the project type
      */
     std::string projectTypeString() const;

     /**
      * @return Complete Project when last task completed status
      */
     inline const bool completeWithLast() const { return _completeWithLast; }

     /**
      * @return List of contexts associated with project
      */
     std::list<const Context *> contexts();

     /**
      * @return List of contexts associated with project
      */
     std::list<const Task *> tasks();

     /**
      * @return Created datetime object
      */
     inline const dt::CTime created() const { return *_created; }

     /**
      * @return Modified datetime object
      */
     inline const dt::CTime modified() const { return *_modified; }

     /**
      * @return Completed datetime object
      */
     inline const dt::CTime completed() const { return *_completed; }
     
     /**
      * @return Dropped datetime object
      */
     inline const dt::CTime dropped() const { return *_dropped; }
     
     /**
      * @return Deferred repeating CTime object
      */
     inline const dt::RepeatingCTime* deferred() const {
         return _deferred.get();
     }
     
     /**
      * @return Due repeating CTime object
      */
     inline dt::RepeatingCTime* due() const {
         return _due.get();
     }

    /********************************* SETTERS ********************************/
    /**
     * Set project name
     * @param projectName
     */
    inline void setProjectName(const std::string& projectName) {
        _projectName = projectName;
        updateModified();
    }

    /**
     * Set notes string
     * @param notes
     */
    inline void setNotes(const std::string& notes) {
        _notes = notes;
        updateModified();
    }

    /**
     * Set Folder
     * @param Folder* folder
     */
    inline void setFolder(const Folder* folder) { _folder = folder; }

    /**
     * Set Status
     * @param status
     */
    inline void setStatus(Status status) {
        _status = status;
        updateModified();
    }

    /**
     * Set project type
     * @param projectType
     */
    inline void setProjectType(ProjectType projectType) {
        _projectType = projectType;
        updateModified();
    }

    /**
     * Set complete with last
     * @param completeWithLast
     */
    inline void setCompleteWithLast(bool completeWithLast) {
        _completeWithLast = completeWithLast;
        updateModified();
    }

    /**
     * Set contexts with an initializer_list
     * @param contexts
     */
    void setContexts(const std::initializer_list<const Context*>& contexts);

    /**
     * Set contexts with list of contexts
     * @param contexts
     */
    void setContexts(const std::list<const Context *> &contexts);

    /**
     * Add a context to the context list
     * @param context
     */
    inline void addContext(const Context* context) {
        _contexts.push_back(context);
        updateModified();
    }

    /**
     * Remove a context from the context list
     * @param context
     * @return raw pointer to a Context*
     */
    const Context* removeContext(const Context* context);

	/**
	 * Set tasks with an initializer_list
	 * @param tasks
	 */
   	void setTasks(const std::initializer_list<const Task*>& tasks);

	/**
	 * Set Tasks with a list
	 */
   	void setTasks(const std::list<const Task*> tasks);	

	/**
	 * Add one task to the list of tasks
	 */
   	void addTask(const Task* task) {
		_tasks.push_back(task);
		updateModified();
	}

    /**
     * Reorder list of tasks
     * @param task Task to move
     * @param location location to place the task in list. Starts at 0
     */
    void reorderTask(const Task* task, int location);

	/**
	 * Remove a task from the list of tasks
	 */ 
	const Task* removeTask(const Task* task);

    /**
     * Set the updated member to current time.
     */
    inline void updateModified() { _modified = std::make_unique<dt::CTime>(); }

    /**
     * Set the status of the project to Status::Complete and update completed
     * CTime member
     */
    void markAsComplete();

    /**
     * Set the deferred member
     * @param deferred
     */
    void setDeferred(dt::RepeatingCTime* deferred) {
         _deferred = std::unique_ptr<dt::RepeatingCTime>(deferred);
         updateModified();
     }

     /**
      * Set the due RepeatingCTime member
      * @param due
      */
    void setDue(dt::RepeatingCTime* due) {
        _due = std::unique_ptr<dt::RepeatingCTime>(due);
        updateModified();
    }
};

} // namespace gtd


#endif //GTD_PROJECT_HPP
