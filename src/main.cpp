#include <memory>
#include <string>
#include <iostream>

//#include "Task.cpp"
#include <sys/stat.h>

#include "Context.hpp"
#include "GtdContainer.hpp"
#include "Project.hpp"
#include "Folder.hpp"

auto
main() -> int {
    const auto contexts  = std::make_shared<gtd::GtdContainer<gtd::Context>>();
    contexts->create(contexts, "c1");
    contexts->create(contexts, "c2");
    contexts->create(contexts, "c3");
    contexts->create(contexts, "c4");
    contexts->create(contexts, "c5");
    contexts->create(contexts, "c6");
    contexts->create(contexts, "c7");

    const auto tasks = std::make_shared<gtd::GtdContainer<gtd::Task>>();
    tasks->create(tasks, "t1");
    tasks->create(tasks, "t2");
    tasks->create(tasks, "t3");
    tasks->create(tasks, "t4");
    tasks->create(tasks, "t5");
    tasks->create(tasks, "t6");
    tasks->create(tasks, "t7");

    const auto folders = std::make_shared<gtd::GtdContainer<gtd::Folder>>();
    folders->create(folders, "F1");
    folders->create(folders, "F2");

    std::cout << "Task table is:    " << tasks->tableName() << std::endl;

    const auto flagged = tasks->getFlagged();

    for ( const auto& task : *tasks ) {
        std::cout << std::boolalpha;
        std::cout << task.name() << " is " << (task.flagged() ? "" : "not ") << "flagged\n";
    }
}
