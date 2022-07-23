//
// Created by George Ford on 6/24/22.
//

#ifndef __GTD_GTDHELPER_HPP__
#define __GTD_GTDHELPER_HPP__

#include <cstring>
#include <string>

using time_point_t = std::chrono::time_point<std::chrono::system_clock>;

namespace gtd {

// ENUMS
/// Task and Task status
enum class Status {
    Active, OnHold, Dropped, Completed, Undefined
} ;

/// Determines how to apply repeat criteria
enum class RepeatFrom {
    Due, Deferred
};

/// Convert string to a Status
Status strToStatus(const std::string& statusStr);

/// Convert a status to a string
std::string statusToStr(Status status);

// Convert string to RepeatFrom enum
std::string repeatFromToStr(RepeatFrom repeatFrom);

/// Convert RepeatFrom enum to string
RepeatFrom strToRepeatFrom(const std::string& repeatFromStr);

/// Return ascii string of a system_clock::time_point
std::string timepointToStr(const time_point_t& tp);

/// \brief enum class describing various types of Projects
enum class ProjectType {
    Parallel, Sequential, SingleActions
};

/// Return string of project type
std::string projectTypeStr(ProjectType projectType);

/// Get ProjectType from string
ProjectType projectTypeFromSr(const std::string & projectTypeStr);

/// \brief enum class describing various types of Projects
enum class TaskType {
    Parallel, Sequential
};

/// Return string of project type
std::string taskTypeString(TaskType taskType);

/// Return TaskType for given string
TaskType taskTypeFromString(const std::string & taskTypeStr);

} // namespace gtd

#endif //__GTD_GTDHELPER_HPP__
