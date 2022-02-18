//
// Created by George Ford on 2/4/22.
//
#include <string>

#include "Status.hpp"

namespace gtd {
std::string statusString(Status status) {
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
}