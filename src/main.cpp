#include <memory>
#include <string>
#include <iostream>
#include <sys/_types/_int64_t.h>

#include "Context.hpp"
#include "Context.hpp"
#include "GtdContainer.hpp"

#include "GtdSqlite.hpp"

// SQLITE INITIATE CONTAINER
/*****************************************************************************/
#include "GtdHelper.hpp"
#include "SQLiteCpp/SQLiteCpp.h"
#include "fmt/base.h"

auto
main() -> int {
    // CONTEXTS
    auto contexts = loadFromDb<gtd::Context>();
    if ( !contexts ) {
        fmt::println("Didn't get contexts");
    }
    for ( int i = 0; const auto& context : *contexts ) {
        fmt::println("context[{}]: {}", i++, context.name());
    }

	auto& context = contexts->at(3);
	context.setNotes("These are the notes", true);

	fmt::println("Context update stack:\n{}", contexts->updateStack().compose());

    // FOLDERS
    auto folders = loadFromDb<gtd::Folder>();
    if ( !folders ) {
        fmt::println("Didn't get folders");
    }
    for ( int i = 0; const auto& folder : *folders ) {
        fmt::println("folder[{}]: {}", i++, folder.name());
    }

    auto projects = loadFromDb<gtd::Project>();
    if ( !projects ) {
        fmt::println("Didn't get projects");
    }
    for ( int i = 0; const auto& project : *projects ) {
        fmt::println("project[{}]: {}", i++, project.name());
    }

    auto tasks = loadFromDb<gtd::Task>();
    if ( !tasks ) {
        fmt::println("Didn't get tasks");
    }
    for ( int i = 0; const auto& task : *tasks ) {
        fmt::println("task[{}]: {}", i++, task.name());
    }
}
