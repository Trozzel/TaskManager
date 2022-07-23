#ifndef __STATUS_HPP__
#define __STATUS_HPP__

#include <algorithm>
#include <cctype>
#include <cwctype>
#include <string>

namespace gtd {

typedef enum {
	Active, OnHold, Dropped, Completed, Undefined
} Status;

Status strToStatus(const std::string& statusStr);
std::string statusToStr(Status status);

} // namespace gtd

#endif // __STATUSBASE_HPP__
