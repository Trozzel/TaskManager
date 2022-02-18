//
// Created by George Ford on 2/15/22.
//

#ifndef GTD_TASK_HPP
#define GTD_TASK_HPP

#include <initializer_list>
#include <memory>
#include <string>
#include <list>

#include "datetime/CTime.hpp"
#include "datetime/RepeatingCTime.hpp"
#include "datetime/datetime.hpp"
#include "Project.hpp"
#include "Status.hpp"
#include "Context.hpp"
#include "Folder.hpp"

namespace gtd {

class Task {
private:
    std::string _taskName{};
    std::string _notes{};
    const Project* _project {nullptr};
    const Task* _parent {nullptr};
    Status _status {Status::Active};

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

// PRIVATE METHODS
private:
	/**
	 * Update the _modified member to current time
	 */ 
	void updateModified() {
		_modified = std::make_unique<dt::CTime>(dt::CTime::currentCTime());
	}

public:
	/**
	 * CTOR
     * Class providing functionality for manipulating tasks from SQLite
     * database.
     * @param std::string taskName
     * @param std::string note
	 * @param const Project* project
     * @param const Task* parent
     * @param Status status
     * @param std::list<const Context*> contexts
     * @param unique_ptr<dt::RepeatingCTime> deferred
     * @param unique_ptr<dt::RepeatingCTime> due
	 */ 
	Task(
			std::string taskName = "New Task",
			std::string notes = "",
			const Project* project = nullptr,
			const Task* parent = nullptr,
			Status status = Status::Active,
			std::list<const Context*> contexts = {},
			std::unique_ptr<dt::RepeatingCTime> deferred = nullptr,
			std::unique_ptr<dt::RepeatingCTime> due = nullptr
		);

	/****************************** GETTERS ***********************************/
	/**
	 * Get task name
	 */ 
	inline std::string taskName() const { return _taskName; }

	/**
	 * Get notes
	 */
    inline std::string notes() { return _notes; }

	/**
	 * Return the owning project
	 */
	inline const Project* project() const { return _project; }	

	/**
	 * Return the Task parent
	 */
   	inline const Task* parent() const { return _parent; }	

	/**
	 * Return copy of the status
	 */
   	inline Status status() const { return _status; }

	/**
	 * Return a copy of the contexts
	 */ 
	inline std::list<const Context*> contexts() const { return _contexts; }
	
	/**
	 * Return dt::CTime, time of creation
	 */
   	inline dt::CTime created() const { return *_created; }	

	/**
	 * Return dt::CTime, time of creation
	 */
   	inline dt::CTime modified() const { return *_modified; }	

	/**
	 * Return dt::CTime, time of creation
	 */
   	inline dt::CTime completed() const { return *_completed; }	

	/**
	 * Return dt::CTime, time of creation
	 */
   	inline dt::CTime dropped() const { return *_dropped; }	

	/**
	 * Return the dt::RepeatingCTime, deferred
	 */
   	inline dt::RepeatingCTime deferred() const { return *_deferred; }	

	/**
	 * Return the dt::RepeatingCTime, due
	 */
   	inline dt::RepeatingCTime due() const { return *_due; }	

	/******************************** SETTERS *********************************/
	/**
	 * Set the task name
	 */ 
	void setTaskName(const std::string& taskName) {
		if (_taskName != taskName) {
			_taskName = taskName;
			updateModified();
		}
	}
	/**
	 * Set the notes
	 */
   	void setNotes(const std::string& notes) {
		if (_notes != notes) {
			_notes = notes;
			updateModified();
		}
	}	

	/**
	 * Set the Project
	 */
   	void setProject(const Project* project);	

	/**
	 * Set parent task
	 */ 
	void setParent(const Task* task);

	/**
	 * Remove Parent
	 */
   	void removeParent() { 
		setParent(nullptr); 
		updateModified();
	}

	/**
	 * Set Status
	 */
   	void setStatus(Status status) {
		_status = status;
		updateModified();
	}	

	/**
	 * Set contexts - std::list
	 */
   	void setContexts(const std::list<const Context*> contexts) {
		_contexts = contexts;
		updateModified();
	}	

	/**
	 * Set contexts - std::initializer_list
	 */
   	void setContexts(const std::initializer_list<const Context*> contexts) {
		_contexts = contexts;
		updateModified();
	}	

	/**
	 * Add a context to the context list
	 */
	void addContext(const Context* context); 

	/**
	 * Remove a context from the Context list
	 */
   	const Context* removeContext(const Context* context);	

	/**
	 * Set completed. NOTE: it is set to NOW automatically
	 */
	void setAsCompleted() {
		_status = Status::Completed;
		*_completed = dt::CTime::currentCTime();
		updateModified();
	}

};

} // namespace gtd

#endif //GTD_TASK_HPP
