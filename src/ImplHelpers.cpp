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
insertContext(std::string_view dbPath, gtd::Context& context) {
	return insertGtdItem<Context>(dbPath, context);
}

std::tuple<int, int>
insertFolder(std::string_view dbPath, gtd::Folder& folder) {
	return insertGtdItem<Folder>(dbPath, folder);
}

std::tuple<int, int>
insertTask(std::string_view dbPath, gtd::Task& task) {
	return insertGtdItem<Task>(dbPath, task);
}

std::tuple<int, int>
insertProject(std::string_view dbPath, gtd::Project& project) {
	return insertGtdItem<Project>(dbPath, project);
}


// READ
/*****************************************************************************/
std::vector<Context>
importContexts(std::string_view pathname, USMgr& updateStackMgr) {
	return importGtdItems<gtd::Context, std::vector<gtd::Context>>(pathname, updateStackMgr);
}

std::vector<Task>
importTasks(std::string_view pathname, USMgr& updateStackMgr) {
	return importGtdItems<gtd::Task, std::vector<gtd::Task>>(pathname, updateStackMgr);
}

std::vector<Project>
importProjects(std::string_view pathname, USMgr& updateStackMgr) {
	return importGtdItems<gtd::Project, std::vector<gtd::Project>>(pathname, updateStackMgr);
}

std::vector<Folder>
importFolders(std::string_view pathname, USMgr& updateStackMgr) {
	return importGtdItems<gtd::Folder, std::vector<gtd::Folder>>(pathname, updateStackMgr);
}

} // namespace gtd
