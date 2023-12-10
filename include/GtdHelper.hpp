//
// Created by George Ford on 6/24/22.
//

#ifndef __GTD_GTDHELPER_HPP__
#define __GTD_GTDHELPER_HPP__

#include <cstring>
#include <filesystem>
#include <iomanip>
#include <string>
#include <string_view>
#include <sstream>
#include <iostream>

#include "fmt/core.h"
#include "toml.hpp"

// Check for compile time RUNMODE
#ifndef RUNMODE
#warning "RUNMODE not set"
#define RUNMODE "dev"
#endif

using time_point_t = std::chrono::time_point<std::chrono::system_clock>;
using unique_id_t = uint64_t;

namespace gtd {

//                                 ENUMS
/*****************************************************************************/
/// Task and Project status
enum class Status {
    Active, OnHold, Dropped, Completed
};

/// \brief Determines how to apply repeat criteria
/// \note Due and Deferred
enum class RepeatFrom {
    Due, Deferred
};

/// \brief enum class describing various types of Tasks
enum class TaskType {
    Parallel, Sequential
};

/// \brief enum class describing various types of Projects
enum class ProjectType {
    Parallel, Sequential, SingleActions
};

/// \brief string_views to eliminate std::string heap allocations
/// \note: string_view copy ctor is noexcept, thus enabling noexcept for
///        string_view returns
// Status strings
static constexpr std::string_view s_strActive{"Active"};
static constexpr std::string_view s_strOnHold{"OnHold"};
static constexpr std::string_view s_strDropped{"Dropped"};
static constexpr std::string_view s_strCompleted{"Completed"};

// Repeat task strings
static constexpr std::string_view s_strDeferred{"Deferred"};
static constexpr std::string_view s_strDue{"Due"};

// Task and Project type strings
static constexpr std::string_view s_strParallel{"Parallel"};
static constexpr std::string_view s_strSequential{"Sequential"};
static constexpr std::string_view s_strSingleActions{"SingleActions"};

// GTD Configuration file
static constexpr std::string_view confFilePath = "../conf/gtd-conf.toml";

/// \brief Get the filename of the database to use from config file
static std::string
getDbConnPath() {
	static bool firstRun = true;
	static std::string tableName;
	if(firstRun) {
		auto config = toml::parse_file(confFilePath);
		if (config.empty()) {
			std::cerr << "Error opening config file\n";
		}
		auto op_tableName = config["database"][fmt::format("{}_db", RUNMODE)]
						 .value<std::string_view>();  // -> std::optional<std::string_view>
		if(op_tableName.has_value()){
			tableName = op_tableName.value();
		} else {
			tableName = "../conf/sql_scripts/gtd_db_dev.db";
		}
		firstRun = false;
	}
	return tableName;
}

/// \brief Convert string to a Status
[[nodiscard]]
constexpr Status strToStatus(std::string_view statusStrIn) {
    Status status;

    if (statusStrIn == "Active") {
        status = Status::Active;
    }
    else if (statusStrIn == "OnHold") {
        status = Status::OnHold;
    }
    else if (statusStrIn == "Dropped") {
        status = Status::Dropped;
    }
    else if (statusStrIn == "Completed") {
        status = Status::Completed;
    }
    else {
        throw std::runtime_error("Unrecognized status string, "
                                 + std::string(statusStrIn));
    }

    return status;
}

/// \brief Convert a status to a string
[[nodiscard]]
constexpr std::string_view statusToStr(Status status) noexcept {
    std::string_view statusStr;
    switch (status) {
    case Status::Active:
        statusStr = std::string_view(s_strActive);
        break;
    case Status::OnHold:
        statusStr = std::string_view(s_strOnHold);
        break;
    case Status::Dropped:
        statusStr = std::string_view(s_strDropped);
        break;
    case Status::Completed:
        statusStr = std::string_view(s_strCompleted);
        break;
    }
    return statusStr;
}

// \brief Convert string to RepeatFrom enum
[[nodiscard]]
constexpr std::string_view repeatFromToStr(RepeatFrom repeatFrom) noexcept {
    std::string_view repeatFromStr;
    switch (repeatFrom) {
    case RepeatFrom::Deferred:
        repeatFromStr = s_strDeferred;
        break;
    case RepeatFrom::Due:
        repeatFromStr = s_strDue;
        break;
    }
    return repeatFromStr;
}

/// \brief Convert RepeatFrom enum to string
[[nodiscard]]
constexpr RepeatFrom strToRepeatFrom(std::string_view repeatFromStr) {
    RepeatFrom repeatFrom;
    if (repeatFromStr == "Deferred") {
        repeatFrom = RepeatFrom::Deferred;
    }
    else if (repeatFromStr == "Due") {
        repeatFrom = RepeatFrom::Due;
    }
    else {
		fmt::println("repeatFromStr: {}", repeatFromStr );
        throw std::runtime_error("error: Unrecognized RepeatFrom string");
    }
    return repeatFrom;
}

/// \brief Return ascii string of a system_clock::time_point
//  definition in GtdHelper.cpp
[[nodiscard]]
std::optional<std::string>
timePointToStr(time_point_t tp);

/// Return string of project type
[[nodiscard]]
constexpr std::string_view 
projectTypeStr(ProjectType projectType) noexcept {
    std::string_view projTypeStr{};
    switch (projectType) {
    case ProjectType::Parallel:
        projTypeStr = s_strParallel;
        break;
    case ProjectType::Sequential:
        projTypeStr = s_strSequential;
        break;
    case ProjectType::SingleActions:
        projTypeStr = s_strSingleActions;
        break;
    }
    return projTypeStr;
}

/// Get ProjectType from string
[[nodiscard]] [[maybe_unused]]
constexpr ProjectType 
projectTypeFromStr(std::string_view projectTypeStr) noexcept {
    ProjectType projectType;
    if (projectTypeStr == "Parallel") {
        projectType = ProjectType::Parallel;
    }
    else if (projectTypeStr == "Sequential") {
        projectType = ProjectType::Sequential;
    }
    else if (projectTypeStr == "SingleActions") {
        projectType = ProjectType::SingleActions;
    }
    else {
		std::cerr << "Unknown ProjectType, '" << projectTypeStr << "'.\n";
		std::cout << "Setting ProjectType to 'Parallel'\n";
		projectType = ProjectType::Parallel;
    }
    return projectType;
}

/// Return string of project type
[[nodiscard]]
constexpr std::string_view 
taskTypeString(TaskType taskType) noexcept {
    std::string_view taskTypeStr{};
    switch (taskType) {
    case TaskType::Parallel:
        taskTypeStr = s_strParallel;
        break;
    case TaskType::Sequential:
        taskTypeStr = s_strSequential;
        break;
    }
    return taskTypeStr;
}

/// Return TaskType for given string
[[maybe_unused]] [[nodiscard]]
constexpr TaskType 
taskTypeFromString(std::string_view taskTypeStr) {
    TaskType taskType;

    // Convert to lowercase for ease of comparison
    if (taskTypeStr == "Parallel") {
        taskType = TaskType::Parallel;
    }
    else if (taskTypeStr == "Sequential") {
        taskType = TaskType::Sequential;
    }
    else {
        throw std::runtime_error("Unknown TaskType string, '"
                                 + std::string(taskTypeStr) + "'");
    }
    return taskType;
}

/// \brief Convert an ASCII time string to chrono::system_clock::time_point
/// \param tpStr ASCII string with format: yyyy-mm-dd hh:mm:ss
[[nodiscard]] [[maybe_unused]]
time_point_t
strToTimePoint(std::string_view tpStr);

} // namespace gtd

#endif //__GTD_GTDHELPER_HPP__
