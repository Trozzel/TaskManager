#include <string>
#include <iostream>

#include <sqlite3.h>

using namespace std;

string valString(char* val) {
	return ((val)? val : "NULL");
}

static int callback (void* data, int numCols, char** values, char** colNames) {
	int status = 0;

	cout << "In callback function" << endl;
	for(int i = 0; i < numCols; ++i) {
		cout << colNames[i] << ": " << valString(values[i]) << endl;
	}
	cout << endl;
	return status;
}

int main(int argc, char* argv[]) 
{
	const char dbPath[] = "../sql_scripts/temp.db";
	sqlite3* db;
	int rc = sqlite3_open(dbPath, &db);

	if(rc) {
		cout << "Could not open the database" << endl;
		sqlite3_close(db);
		return 1;
	}

	char* errMsg;
	char sql[] = "SELECT * FROM contexts";
	sqlite3_exec(db, sql, callback, NULL, &errMsg);

	sqlite3_close(db);
}
