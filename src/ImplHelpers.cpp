#include "ImplHelpers.hpp"
#include "Context.hpp"
#include "Folder.hpp"
#include "GtdBase.hpp"
#include "Project.hpp"
#include "Task.hpp"

namespace gtd {

// INSERT
/*****************************************************************************/
std::tuple<int, int>
insertContext(std::string_view dbPath, Context& context) {
	return insertGtdItem<Context>(dbPath, context);
}

std::tuple<int, int>
insertFolder(std::string_view dbPath, Folder& folder) {
	return insertGtdItem<Folder>(dbPath, folder);
}

std::tuple<int, int>
insertTask(std::string_view dbPath, Task& task) {
	return insertGtdItem<Task>(dbPath, task);
}

std::tuple<int, int>
insertProject(std::string_view dbPath,Project& project) {
	return insertGtdItem<Project>(dbPath, project);
}


// READ
/*****************************************************************************/
std::vector<Context>
importContexts(std::string_view pathname, USMgr& updateStackMgr) {
	return importGtdItems<Context, std::vector<Context>>(pathname, updateStackMgr);
}

std::vector<Task>
importTasks(std::string_view pathname, USMgr& updateStackMgr) {
	return importGtdItems<Task, std::vector<Task>>(pathname, updateStackMgr);
}

std::vector<Project>
importProjects(std::string_view pathname, USMgr& updateStackMgr) {
	return importGtdItems<Project, std::vector<Project>>(pathname, updateStackMgr);
}

std::vector<Folder>
importFolders(std::string_view pathname, USMgr& updateStackMgr) {
	return importGtdItems<Folder, std::vector<Folder>>(pathname, updateStackMgr);
}

} // namespace gtd
