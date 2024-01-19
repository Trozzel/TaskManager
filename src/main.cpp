#include <memory>
#include <string>
#include <iostream>

//#include "Task.cpp"
#include <sys/stat.h>

#include "Context.hpp"
#include "GtdContainer.hpp"
#include "GtdHelper.hpp"
#include "Project.hpp"
#include "Folder.hpp"
#include "fmt/base.h"

auto
main() -> int {
    const auto contexts  = std::make_shared<gtd::GtdContainer<gtd::Context>>();
    auto& context = contexts->create(contexts, "c1");
    {
        context = contexts->create(contexts, "c2");
        context.setName("Boogor", true);
    }

    {
        context = contexts->create(contexts, "c4");
        context.setNotes("These are some notes", true);
    }
    contexts->create(contexts, "c5");
    contexts->create(contexts, "c6");
    contexts->create(contexts, "c7");

    std::cout << contexts->updateStack().compose(gtd::GtdType::Context) << std::endl;

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

}
