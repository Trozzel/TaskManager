//
// Created by George Ford on 6/24/22.
//
#include <fmt/chrono.h>

#include "GtdHelper.hpp"

using namespace std;

namespace gtd {

Status strToStatus(const std::string& statusStrIn) {
    Status status = Status::Undefined;
    string statusStr;

    // Convert to lower case
    std::transform(statusStrIn.begin(), statusStrIn.end(),
                   back_inserter(statusStr),
                   [](char c){ return tolower(c); } );

    if(statusStr == "active")
        status = Status::Active;
    else if (statusStr == "onhold")
        status = Status::OnHold;
    else if (statusStr == "dropped")
        status = Status::Dropped;
    else if (statusStr == "completed")
        status = Status::Completed;

    return status;
}

std::string statusToStr(Status status) {
    string statusStr;
    switch (status) {
    case Status::Active:
        statusStr = "Active";
        break;
    case Status::OnHold:
        statusStr = "On Hold";
        break;
    case Status::Dropped:
        statusStr = "Dropped";
        break;
    case Status::Completed:
        statusStr = "Completed";
        break;
    case Status::Undefined:
        statusStr  ="Undefined";
        break;
    default:
        statusStr = "Undefined";
        break;
    }
    return statusStr;
}

std::string repeatFromToStr(RepeatFrom repeatFrom) {
    string repeatFromStr;
    switch(repeatFrom) {
    case RepeatFrom::Deferred:
        repeatFromStr = "deferred";
        break;
    case RepeatFrom::Due:
        repeatFromStr = "due";
        break;
    default:
        throw runtime_error("Invalid RepeatFrom type");
    }
    return repeatFromStr;
}

RepeatFrom strToRepeatFrom(const string &repeatFromStr) {
    // Convert to lowercase
    string rfs = repeatFromStr;
    std::transform(rfs.begin(), rfs.end(), rfs.begin(), [](char c) { return ::tolower(c); });

    RepeatFrom repeatFrom;
    if(repeatFromStr == "deferred") {
        repeatFrom = RepeatFrom::Deferred;
    }
    else if(repeatFromStr == "due") {
        repeatFrom = RepeatFrom::Due;
    }
    else {
        throw runtime_error("Unrecognized RepeatFrom string");
    }
    return repeatFrom;
}

std::string timepointToStr(const time_point_t &tp) {
    return fmt::format("{}", tp);
}

string projectTypeStr(ProjectType projectType) {
    std::string projTypeStr{};
    switch (projectType) {
    case ProjectType::Parallel:
        projTypeStr = "Parallel";
        break;
    case ProjectType::Sequential:
        projTypeStr = "Sequential";
        break;
    case ProjectType::SingleActions:
        projTypeStr = "SingleActions";
        break;
    }
    return projTypeStr;
}

ProjectType projectTypeFromSr(const std::string & projectTypeStr) {
    // Convert to lowercase for ease of comparison
    string pts(projectTypeStr);
    transform(pts.begin(), pts.end(), pts.begin(), [](char c) { return ::tolower(c); });

	ProjectType pt;

    if(pts == "parallel") {
        pt = ProjectType::Sequential;
    }
    else if(pts == "sequential") {
        pt = ProjectType::Sequential;
    }
    else if(pts == "singleactions") {
        pt = ProjectType::SingleActions;
    }
    else {
        throw runtime_error("Unknown ProjectType string, '" + pts + "'");
    }
    return pt;

}

std::string taskTypeString(TaskType taskType) {
    std::string taskTypeStr{};
    switch (taskType) {
    case TaskType::Parallel:
        taskTypeStr = "Parallel";
        break;
    case TaskType::Sequential:
        taskTypeStr = "Sequential";
        break;
    }
    return taskTypeStr;
}

TaskType taskTypeFromString(const string &taskTypeStr) {
    TaskType taskType;

    // Convert to lowercase for ease of comparison
    string tts(taskTypeStr);
    transform(tts.begin(), tts.end(), tts.begin(), [](char c) { return ::tolower(c); });
    if(taskTypeStr == "parallel") {
        taskType = TaskType::Sequential;
    }
    else if(taskTypeStr == "sequential") {
        taskType = TaskType::Sequential;
    }
    else {
        throw runtime_error("Unknown TaskType string, '" + taskTypeStr + "'");
    }
    return taskType;
}


} // namespace gtd

