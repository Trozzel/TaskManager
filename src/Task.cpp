//
// Created by George Ford on 1/28/22.
//
#include "Task.hpp"
#include "GtdContainer.hpp"
#include "UpdateStack.hpp"


namespace gtd {
// CTORS
/*****************************************************************************/
Task::Task( const pContainer gtdItems, const std::string_view name ) :
	Completable(name),
	_gtdItems(gtdItems)
{}

Task::Task( const Task& other ) :
	Completable(other),
	_gtdItems(other._gtdItems),
	_taskType(other._taskType),
	_projectId(other._projectId)
{}

Task::Task( Task&& other ) noexcept :
	Completable(other),
	_gtdItems(std::move(other._gtdItems)),
	_taskType(other._taskType),
	_projectId(std::move(other._projectId))
{}

// ASSIGMENT OPERATORS
/*****************************************************************************/
Task&
Task::operator=( const Task& other ) {
	if(&other != this) {
		Completable::operator=(other);
		_gtdItems = other._gtdItems;
		_taskType = other._taskType;
		_projectId = other._projectId;
	}
	return *this;
}

Task&
Task::operator=( Task&& other ) {
	if(&other != this) {
		Completable::operator=(other);
		_gtdItems = std::move(other._gtdItems);
		_taskType = other._taskType;
		_projectId = std::move(other._projectId);
	}
	return *this;
}

// SETTERS
/*****************************************************************************/
void
Task::setProjectId( const unique_id_t projectId, const bool update ) {
	if constexpr(gtd_category::gtd_type == GtdType::Task) {
		_projectId = projectId;
		if ( _o_uniqueId ) {
			auto& us = _gtdItems->updateStack();
			us.push(*uniqueId(), "projectId", *this->projectId());
		}
	}
	else {
		std::cerr << "'*this' must meet gtd_category::gtd_type == Gtd::Task\n";
	}
}

void
Task::setTaskType( const TaskType taskType, const bool update ) {
	if constexpr(gtd_category::gtd_type == GtdType::Task) {
		_taskType = taskType;
		if ( (_o_uniqueId) ) {
			auto& us = _gtdItems->updateStack();
			us.push(*uniqueId(), "taskType", taskTypeString(taskType));
		}
	}
	else {
		std::cerr << "'*this' must meet gtd_category::gtd_type == Gtd::Task\n";
	}
}

void
Task::setTaskType( const std::string_view taskType, const bool update ) {
	if constexpr(gtd_category::gtd_type == GtdType::Task) {
		_taskType = strToTaskType(taskType);
		if ( (_o_uniqueId) ) {
			auto& us = _gtdItems->updateStack();
			us.push(*uniqueId(), "taskType", taskTypeString(_taskType));
		}
	}
	else {
		std::cerr << "'*this' must meet gtd_category::gtd_type == Gtd::Task\n";
	}
}

//sdefaulttd::ostream&
//operator<<( std::ostream& out, const Task& task ) {
//    // SEND BASE TO STREAM
//	const auto pUpdateStack = _updateStackMgr.getUpdateStack();
//    out << *pBase;
//
//    // SEND REMAINED TO STREAM
//    out << *task.notes() << " "
//            << *task.deferredStr() << " "
//            << *task.dueStr() << " "
//            << taskTypeString(task.taskType()) << " "
//            << ios::boolalpha << task.isRepeating();
//
//    return out;
//}
} // namespace gtd
