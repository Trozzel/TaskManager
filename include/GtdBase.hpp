#ifndef __GTDBASE_HPP__
#define __GTDBASE_HPP__

#include <cstring>
#include <exception>
#include <sstream>
#include <iomanip>
#include <memory>
#include <string>
#include <chrono>
#include <cctype>

#include <fmt/chrono.h>

#include "GtdHelper.hpp"

using ULL = unsigned long long;

namespace gtd {

class GtdBase {

protected:
    ULL          _uniqueId;
    std::string  _name;
    Status       _status;
    time_point_t _created;
    time_point_t _modified;
    ULL          _parentId;    // _parentId == 0 --> no parent

    /// Convert an ASCII time string to chrono::system_clock::time_point
    /// \param tpStr ASCII string with format: yyyy-mm-dd hh:mm:ss
    static time_point_t strToTimePoint(const std::string &tpStr) {
        std::tm           tm = {};
        std::stringstream ss(tpStr);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
        return std::chrono::system_clock::from_time_t(std::mktime(&tm));
    }

public:
    // CTORS
    /**************************************************************************/
    GtdBase() = default;

    explicit GtdBase(std::string name) :
            _name(std::move(name)) {
    }

    // BY READING IN DATA AS STRINGS
    GtdBase(const std::string &uniqueIdStr,
            const std::string &name,
            const std::string &statusStr,
            const std::string &createdStr,
            const std::string &modifiedStr,
            const std::string &parentIdStr = "") :
            _uniqueId(stoll(uniqueIdStr)),
            _name(name),
            _status(strToStatus(statusStr)),
            _parentId(stoll(parentIdStr)) {
        // IF CREATED STRING IS EMPTY
        if (createdStr.empty()) {
            _created = std::chrono::system_clock::now();
        }
            // MAKE _created == NOW
        else {
            _created = strToTimePoint(createdStr);
        }
        if (modifiedStr.empty()) {
            _modified = std::chrono::system_clock::now();
        }
        else {
            _modified = strToTimePoint(modifiedStr);
        }
    }

    virtual ~GtdBase() = default;

    // GETTERS
    /**************************************************************************/
    inline ULL uniqueId() const { return _uniqueId; }

    inline std::string name() { return _name; }

    inline Status status() { return _status; }

    std::string statusStr() { return statusToStr(_status); }

    inline time_point_t
    created() { return _created; }

    std::string createdStr() { return fmt::format("{}", _created); }

    inline time_point_t
    modified() { return _modified; }

    std::string modifiedStr() { return fmt::format("{}", _modified); }

    virtual inline ULL parentId() const { return _parentId; }

    // SETTERS
    void setUniqueId(const std::string &uniqueIdStr) {
        _uniqueId = stoll(uniqueIdStr);
    }

    void setUniqueId(ULL id) {
        _uniqueId = id;
    }

    void setName(const std::string &name) {
        _name = name;
    }

    void setStatus(const std::string &statusStr) {
        _status = strToStatus(statusStr);
    }

    void setStatus(Status status) {
        _status = status;
    }

    void setCreated(const std::string &created) {
        _created = strToTimePoint(created);
    }

    void setCreated(const time_point_t &tp) {
        _created = tp;
    }

    void setModified(const std::string &modified) {
        _modified = strToTimePoint(modified);
    }

    void setModified(const time_point_t &tp) {
        _modified = tp;
    }

    virtual void setParentId(const std::string &parentIdStr) {
        _parentId = stoll(parentIdStr);
    }

    virtual void setParentId(ULL id) {
        _parentId = id;
    }

    friend std::ostream &operator<<(std::ostream &out, const GtdBase &base) {
        out << base._uniqueId << " " << base._name << " "
            << statusToStr(base._status) << " "
            << fmt::format("{} ", base._created)
            << fmt::format("{} ", base._modified)
            << base._parentId;

        return out;
    };

};

} // namespace gtd

#endif // __GTDBASE_HPP__
