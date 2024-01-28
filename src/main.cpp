#include <memory>
#include <string>
#include <iostream>
#include <sys/_types/_int64_t.h>

#include "GtdContainer.hpp"
#include "GtdHelper.hpp"
#include "fmt/base.h"

auto
main() -> int {
    // CONTEXTS
	auto c1 = gtd::Context(nullptr, "name");
    auto& contexts = gtd::GtdContainer<gtd::Context>::initFromDb();
	fmt::println("contexts: {}", contexts.use_count());
	contexts->attach(c1);
	fmt::println("contexts: {}\n\n", contexts.use_count());
	
    if ( contexts->empty() ) {
        fmt::println("Didn't get contexts");
    }
    for ( int i = 0; const auto& context : *contexts ) {
        fmt::println("context[{}]: {}", i++, context.name());
    }

	auto& context = contexts->at(3);
	context.setNotes("These are the notes", true);
	context.setStatus(gtd::Status::Dropped, true);

	fmt::println("Context update stack:\n{}", contexts->updateStack().compose());

    // FOLDERS
    auto& folders = gtd::GtdContainer<gtd::Folder>::initFromDb();
    if ( folders->empty() ) {
        fmt::println("Didn't get folders");
    }
    for ( int i = 0; const auto& folder : *folders ) {
        fmt::println("folder[{}]: {}", i++, folder.name());
    }

	// PROJECTS
    auto projects = std::move(gtd::GtdContainer<gtd::Project>::initFromDb());
    if ( projects->empty() ) {
        fmt::println("Didn't get projects");
    }
    for ( int i = 0; const auto& project : *projects ) {
        fmt::println("project[{}]: {}", i++, project.name());
    }

	// TASKS
    auto& tasks = gtd::GtdContainer<gtd::Task>::initFromDb();
    if ( tasks->empty() ) {
        fmt::println("Didn't get tasks");
    }
    for ( int i = 0; const auto& task : *tasks ) {
        fmt::println("task[{}]: {}", i++, task.name());
    }

	// PRINT USE COUNTS
	fmt::println("contexts use count: {}", contexts.use_count());
	fmt::println("folders use count: {}", folders.use_count());
	fmt::println("projects use count: {}", projects.use_count());
	fmt::println("tasks use count: {}", tasks.use_count());
}
