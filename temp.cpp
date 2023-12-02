#include <__ranges/filter_view.h>
#include <__ranges/transform_view.h>
#include <algorithm>
#include <complex>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>
#include <ranges>
	
#include "SQLiteCpp/SQLiteCpp.h"
#include "Folder.hpp"
#include "Project.hpp"
#include "Task.hpp"
#include "Context.hpp"
#include "ImplHelpers.hpp"

/// \brief Format the columns to same size
template<typename Gtd>
void
formatColumns(const std::vector<const Gtd> & gtdItems) {
	static_assert(std::is_base_of_v<gtd::GtdBase, Gtd>); // ensure gtd object
	// Initialize longest string lengths
	size_t longestName = 0;
	size_t longestStatus = 0;

	// 1. find longest row
	for(const auto & gtdItem : gtdItems) {
		// 1. find longest string for each field in all items
		longestName = (gtdItem.name().length() > longestName) ?
			gtdItem.name().length() : longestName;
		longestStatus = (gtdItem.statusStr().length() > longestStatus) ?
			gtdItem.statusStr().length() : longestStatus;
	}
	longestName++; longestStatus++;

	// 2. Format all fields for all records into equal column len
	std::cout << std::left << std::setw(longestName) << "TASK" << "| ";
	std::cout << std::left << std::setw(longestStatus) << "STATUS";
	std::cout << std::endl;
	std::cout << std::setfill('-') << std::left <<  std::setw(longestName + longestStatus + 1) << '-';
	std::cout << std::setfill(' ') << std::endl;
	using GtdTable = std::vector<std::vector<std::string_view>>;
	GtdTable rows(gtdItems.size());
	for(const auto & gtdItem : gtdItems) {
		std::cout << std::left << std::setw(longestName)   << gtdItem.name() << "| ";
		std::cout << std::left << std::setw(longestStatus) << gtdItem.statusStr();
		std::cout << std::endl;
	}
}

// MAIN
/*****************************************************************************/
int main()
{
    auto contexts = gtd::importContexts("../sql_scripts/temp.db");
    auto tasks    = gtd::importTasks("../sql_scripts/temp.db");
    auto projects = gtd::importProjects("../sql_scripts/temp.db");
    auto folders  = gtd::importFolders("../sql_scripts/temp.db");

    if(tasks.empty()) {
		fmt::println(stderr, "Did not find any tasks");
		return 1;
    }

	// Get parents from all tasks
	auto childToParent = tasks 
		| std::views::filter([](const auto& task) {
				return task.parentId() != -1;
				})
		| std::views::transform([&tasks](const auto& task) {
				return std::make_pair(task, *getParent_it(task, tasks));
				});
	
	for(const auto& p2c : childToParent) {
		std::cout << p2c.first.name() << " -> " << p2c.second.name() << std::endl;
	}
}
