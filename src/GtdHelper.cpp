//
// Created by George Ford on 6/24/22.
//
#include <fmt/chrono.h>

#include "GtdHelper.hpp"

using namespace std;

namespace gtd {

std::string timePointToStr(time_point_t tp) {
    using chrono::system_clock;
    // YEAR 2000 RAW TIME
    static const long y2000_t = 949881676;

    // RETURN TIME STRING FROM system_clock::time_point
    // Returns "NULL" if before year 2000
    auto tp_t = system_clock::to_time_t(tp);
    if (tp_t < y2000_t) {
        return "NULL";
    }
    else {
        return fmt::format("{} ", tp);
    }
}

time_point_t strToTimePoint(std::string_view tpStr) {
    std::tm tm = {};
    std::stringstream ss(tpStr.data());
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

} // namespace gtd

