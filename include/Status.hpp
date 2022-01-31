//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_APP_STATUS_HPP
#define GTD_APP_STATUS_HPP

#include <string>


namespace gtd {

/**
 * @brief gtd::Status enum.
 * @details Describes status of task or project
 */
enum class Status {
    Active, Hold, Completed, Dropped
};

/**
 * @brief Get String of enum class Status
 * @param status is status from enum Status
 * @return string describing the status of project or task
 */
[[maybe_unused]] std::string statusString(Status status) {
    std::string statString {};
    switch (status) {
        case Status::Active:
            statString = "Active";
            break;
        case Status::Completed:
            statString = "Completed";
            break;
        case Status::Dropped:
            statString = "Dropped";
            break;
        case Status::Hold:
            statString = "Hold";
            break;
        }
    return statString;
}

} // namespace gtd
#endif//GTD_APP_STATUS_HPP
