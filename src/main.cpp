#include <exception>
#include <memory>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sys/_types/_int64_t.h>

#include "GtdContainer.hpp"
#include "GtdHelper.hpp"
#include "UpdateStack.hpp"
#include "fmt/base.h"
#include "fmt/chrono.h"

auto
main() -> int {
    // CONTEXTS
	auto c1 = gtd::Context(nullptr, "name");
    auto& contexts = gtd::GtdContainer<gtd::Context>::initFromDb();
	contexts->attach(c1);
	
	fmt::println("Contexts created after January 2");
	for(const auto context : contexts->getAfterCreated("2023-01-02 00:00:00")) {
		fmt::println("Context: '{}', [{}]; created: {:%F %r}",
				context.name(), *context.uniqueId(), context.created());
	}

	auto& context = contexts->at(3);
	context.setNotes("These are the notes", true);
	context.setStatus(gtd::Status::Dropped, true);

	contexts->updateDb();

	auto res = contexts->getByName("NAME", true);
	for (auto& r : res) {
		fmt::println("Removing '{}'[{}]", r.name(), *r.uniqueId());
		contexts->removeItem(r);
	}
	
    // FOLDERS
    auto& folders = gtd::GtdContainer<gtd::Folder>::initFromDb();
	
	// PROJECTS
    auto& projects = gtd::GtdContainer<gtd::Project>::initFromDb();

	// CREATE PROJECT - Finish taxes
	auto project = gtd::Project(nullptr, "Finish taxes");
	project.setDue("2024-04-15 16:30:00", false);
	project.setProjectType(gtd::ProjectType::Sequential, false);
	projects->attach(project);

	// TASKS
    auto& tasks = gtd::GtdContainer<gtd::Task>::initFromDb();

	// CREATE TASKS FOR PROJECT Finish taxes
	auto taxes = projects->getByName("Finish taxes").front();
	auto task1 = gtd::Task(nullptr, "Organize documents");
	task1.setDue("2024-02-01 16:30:00", false);
	task1.setContext(contexts->getByName("Home").front(), false);
	task1.setProject(taxes, false);

	auto task2 = gtd::Task(nullptr, "Find last year's taxes");
	task2.setContext(contexts->getByName("Computer").front(), false);
	task2.setProject(taxes, false);
	tasks->attach(task1);
	tasks->attach(task2);

	auto home = contexts->getByName("Home").front();
	auto homeTasks = tasks->getWithContext(home);
	fmt::println("Tasks with context: '{}'", home.name());
	for (const auto & task : homeTasks) {
		fmt::println("'{}'", task.name());
	}

	// PRINT USE COUNTS
	fmt::println("contexts use count: {}", contexts.use_count());
	fmt::println("folders use count:  {}", folders.use_count());
	fmt::println("projects use count: {}", projects.use_count());
	fmt::println("tasks use count:    {}", tasks.use_count());
}
