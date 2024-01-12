#include <memory>
#include <string>
#include <iostream>

//#include "Task.cpp"
#include "Context.hpp"
#include "Folder.hpp"
#include "Project.hpp"
#include "GtdContainer.hpp"

auto
main() -> int {
    const auto tasks = std::make_shared<gtd::GtdContainer<gtd::Task>>();
    auto& t1 = tasks->create(tasks, "George");
    auto& t2 = tasks->create(tasks, "George Isaac");
    t2.setFlagged(true);

    const auto folders = std::make_shared<gtd::GtdContainer<gtd::Folder>>();
    auto&      f1      = folders->create(folders, "F1");
    auto&      f2      = folders->create(folders, "F2");

    std::cout << "Task table is:    " << tasks->tableName() << std::endl;
    //std::cout << "Context table is: " << contexts->tableName() << std::endl;

    const auto flagged = tasks->getFlagged();

    for ( const auto& item : flagged ) {
        std::cout << "Printing flagged tasks...\n";
        std::cout << item.name() << std::endl;
    }

    for ( const auto& task : *tasks ) {
        std::cout << std::boolalpha;
        std::cout << task.name() << " is " << (task.flagged() ? "" : "not ") << "flagged\n";
    }
}
