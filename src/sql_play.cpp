#include <exception>
#include <map>
#include <sstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <fmt/format.h>

#include <sqlite3.h>

#include "Project.hpp"
#include "Context.hpp"
#include "Folder.hpp"
#include "Task.hpp"

using namespace std;
using namespace gtd;

using db_t = map<string, vector<string>>;

// Returns nullptr as string, "NULL"
string valString(const char* val) {
	return ((val)? val : "NULL");
}

bool populateBase(GtdBase* pBase, const char* val, const char* colName) {
    bool found = true;
    if(!strcmp(colName, "uniqueId")) {
        pBase->setUniqueId(val);
    }
    else if(!strcmp(colName, "name")) {
        pBase->setName(val);
    }
    else if(!strcmp(colName, "parentId")) {
        if(val != NULL) {
            pBase->setParentId(val);
        }
        else {
            pBase->setParentId(0);
        }
    }
    else if(!strcmp(colName, "status")) {
        pBase->setStatus(val);
    }
    else if(!strcmp(colName, "created")) {
        pBase->setCreated(val);
    }
    else if(!strcmp(colName, "modified")) {
        pBase->setModified(val);
    }
    else
        found = false;

    return found;
}

bool populateTask(Task* pTask, const char* val, const char* colName) {
    bool found = true;

    if(!strcmp(colName, "deferred")) {
        pTask->setDeferred(valString(val));
    }
    else if(!strcmp(colName, "due")) {
        pTask->setDue(valString(val));
    }
    else if(!strcmp(colName, "repeating")) {
        pTask->setIsRepeating(val);
    }
    else if(!strcmp(colName, "repeatFrom")) {
        pTask->setRepeatFrom(valString(val));
    }
    else if(!strcmp(colName, "repeatEveryFile")) {
        pTask->setRepeatFromPath(valString(val));
    }
    else if(!strcmp(colName, "created")) {
        pTask->setCreated(val);
    }
    else if(!strcmp(colName, "modified")) {
        pTask->setModified(val);
    }
    else if(!strcmp(colName, "contextId")) {
        pTask->setModified(valString(val));
    }
    else if(!strcmp(colName, "projectId")) {
        pTask->setModified(valString(val));
    }
    else
        found = false;

    return found;
}

bool populateProject(Project* pProject, const char* val, const char* colName) {
    bool found = true;

    if(!strcmp(colName, "deferred")) {
        pProject->setDeferred(valString(val));
    }
    else if(!strcmp(colName, "due")) {
        pProject->setDue(valString(val));
    }
    else if(!strcmp(colName, "repeating")) {
        pProject->setIsRepeating(val);
    }
    else if(!strcmp(colName, "repeatFrom")) {
        pProject->setRepeatFrom(valString(val));
    }
    else if(!strcmp(colName, "repeatEveryFile")) {
        pProject->setRepeatFromPath(valString(val));
    }
    else if(!strcmp(colName, "created")) {
        pProject->setCreated(val);
    }
    else if(!strcmp(colName, "modified")) {
        pProject->setModified(val);
    }
    else if(!strcmp(colName, "contextId")) {
        pProject->setModified(valString(val));
    }
    else if(!strcmp(colName, "projectId")) {
        pProject->setModified(valString(val));
    }
    else
        found = false;

    return found;

}

bool getEntry(db_t * dbData, const char * val, const char * colName) {
	bool success = true;
	
	try {
		dbData->at(colName).push_back(val);
	}
	catch (const exception& e) {
		fmt::print(stderr, "Error placing value into map: {}\n", e.what());
		success = false;
	}
	return success;
}

template<typename T>
static int baseCallback (void* data, int numCols, char** values, char** colNames) {
	int status = 0;

	static auto container = static_cast<vector<T>*>(data);

    T gtdPt;
	for(int i = 0; i < numCols; ++i) {
		if(!populateBase(&gtdPt, values[i], colNames[i])) {
            fmt::print(stderr, "Unrecognized col name, '{}'\n", colNames[i]);
		}
	}
    container->push_back(gtdPt);
	return status;
}

template<typename T>
static int taskCallback (void* data, int numCols, char** values, char** colNames) {
    int status = 0;

    static auto container = static_cast<vector<T>*>(data);

    T gtdPt;
    for(int i = 0; i < numCols; ++i) {
        if(!populateBase(&gtdPt, values[i], colNames[i])) {
            if(!populateTask(&gtdPt, values[i], colNames[i])) {
                cout << "Unrecognized column name, '" << colNames[i] << "'" << endl;
            }
        }
    }
    container->push_back(gtdPt);
    return status;
}

template<typename T>
static int projectCallback (void* data, int numCols, char** values, char** colNames) {
    int status = 0;

    static auto container = static_cast<vector<T>*>(data);

    T gtdPt;
    for(int i = 0; i < numCols; ++i) {
        if(!populateBase(&gtdPt, values[i], colNames[i])) {
            if(!populateProject(&gtdPt, values[i], colNames[i])) {
                cout << "Unrecognized column name, '" << colNames[i] << "'" << endl;
            }
        }
    }
    container->push_back(gtdPt);
    return status;
}

static int entryCallback(void * data, int numCols, char** values, char** colNames) {
	int status = 0;
	db_t * db = static_cast<db_t*>(data);

	for(int i = 0; i < numCols; ++i) {
		const string & colName = colNames[i];
		const string & value   = valString(values[i]);
		//if(db->contains(colName)) {
		//	db->at(colName).push_back(value);
		//}
		//else {
		//	db->insert_or_assign(colName, vector<string>{value});
		//}
		(*db)[colNames[i]].push_back(valString(values[i]));
	}

	return status;
}

void entryPrinter(const db_t & db) {
	for(auto & entry : db) {
		cout << entry.first << "\t";
	}
	cout << endl;

	int count = 0;
	for(auto & entry : db) {
		for(auto & val : entry.second) {
			cout << val << string("\t", count) << endl;
		}
		++count;
	}
}


int main(int argc, char* argv[]) 
{
	const char dbPath[] = "../sql_scripts/temp.db";
	sqlite3* db;
	int rc = sqlite3_open(dbPath, &db);

	if(rc) {
		cout << "Could not open the database" << endl;
		sqlite3_close(db);
		return rc;
	}

	char* errMsg;

	db_t data;
	char sql1[] = "SELECT * FROM projects";
    sqlite3_exec(db, sql1, entryCallback, &data, &errMsg);

	sqlite3_close(db);

	entryPrinter(data);
}

