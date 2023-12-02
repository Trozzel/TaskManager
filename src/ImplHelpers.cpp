#include "ImplHelpers.hpp"
#include "Folder.hpp"
#include "Project.hpp"
#include "Task.hpp"

namespace gtd {
std::vector<Context>
importContexts(std::string_view pathname) {
	return importGtdItems<gtd::Context, std::vector<gtd::Context>>(pathname);
}

std::vector<Task>
importTasks(std::string_view pathname) {
	return importGtdItems<gtd::Task, std::vector<gtd::Task>>(pathname);
}

std::vector<Project>
importProjects(std::string_view pathname) {
	return importGtdItems<gtd::Project, std::vector<gtd::Project>>(pathname);
}

std::vector<Folder>
importFolders(std::string_view pathname) {
	return importGtdItems<gtd::Folder, std::vector<gtd::Folder>>(pathname);
}

} // namespace gtd
