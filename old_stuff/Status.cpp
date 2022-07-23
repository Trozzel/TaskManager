//
// Created by George Ford on 2/4/22.
//
#include <string>

#include "Status.hpp"

using namespace std;

namespace gtd {

Status strToStatus(const std::string& statusStrIn) {
	Status status = Undefined;
	string statusStr;

	// Convert to lower case
	std::transform(statusStrIn.begin(), statusStrIn.end(), 
			back_inserter(statusStr),
			[](char c){ return tolower(c); } );

	if(statusStr == "active")
		status = Active;
	else if (statusStr == "onhold")
		status = OnHold;
	else if (statusStr == "dropped")
		status = Dropped;
	else if (statusStr == "completed")
		status = Completed;

	return status;
}

std::string statusToStr(Status status) {
	string statusStr;
	switch (status) {
		case Active:
			statusStr = "Active";
			break;
		case OnHold:
			statusStr = "On Hold";
			break;
		case Dropped:
			statusStr = "Dropped";
			break;
		case Completed:
			statusStr = "Completed";
			break;
		case Undefined:
			statusStr  ="Undefined";
			break;
		default:
			statusStr = "Undefined";
			break;
	}
	return statusStr;
}

} // namespace gtd
