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
	
#include "CompletableBase.hpp"
#include "Folder.hpp"
#include "GtdBase.hpp"
#include "Project.hpp"
#include "SQLiteCpp/SQLiteCpp.h"
#include "Task.hpp"
#include "Context.hpp"


/// \brief Get Gtd Items from db
template<typename Gtd_t, typename VectorGtd>
VectorGtd
importGtdItems(std::string_view pathname) {
	static_assert(std::is_base_of_v<gtd::GtdBase, Gtd_t>);
	static_assert(std::is_base_of_v<gtd::GtdBase, typename VectorGtd::value_type>);
	typename std::remove_const_t<VectorGtd> gtdItems;
    try {
        SQLite::Database db(pathname);
		const size_t tableStrSz {10};
		char table[10] = "tasks";
		if(std::is_same_v<Gtd_t, gtd::Project>) {
			strncpy(table, "projects", tableStrSz);
		}
		const size_t selectStmtSz {50};
		char queryStmt[50] = "SELECT * FROM ";
		strncat(queryStmt, table, selectStmtSz);
        SQLite::Statement query(db, queryStmt);

		// FOR PRINTING DIAGNOSTICS
		table[strlen(table) - 1] = '\0';
		table[0] = table[0] - 32;

        while(query.executeStep()) {
			int colnum {0};
            Gtd_t gtdItem{};
            gtdItem.setUniqueId(query.getColumn(colnum++)); // 0
            gtdItem.setName(std::string_view(query.getColumn(colnum++))); // 1
			if(!query.isColumnNull(colnum++)) { //2
				gtdItem.setParentId(query.getColumn(colnum - 1));
			}
            gtdItem.setStatus(std::string_view(query.getColumn(colnum++)));
            gtdItem.setCreated(std::string_view(query.getColumn(colnum++)));
            gtdItem.setModified(std::string_view(query.getColumn(colnum++)));
			if constexpr(std::is_base_of_v<gtd::CompletableBase, Gtd_t>) {
				if(!query.isColumnNull(colnum++)) {
					gtdItem.setContextId(query.getColumn(colnum - 1));
				}
				if constexpr(std::is_same_v<Gtd_t, gtd::Task>) {
					if(!query.isColumnNull(colnum++)) {
						gtdItem.setProjectId(query.getColumn(colnum - 1).getInt());
					}
				} else { // dealing with a gtd::Project
					if(!query.isColumnNull(colnum++)) {
						gtdItem.setFolderId(query.getColumn(colnum - 1).getInt());
					}
				}
				gtdItem.setFlagged(query.getColumn(colnum++));
				if(!query.isColumnNull(colnum++)) {
					gtdItem.setDeferred(std::string_view(query.getColumn(colnum - 1)));
				}
				if(!query.isColumnNull(colnum++)) {
					gtdItem.setDue(std::string_view(query.getColumn(colnum - 1)));
				}
				gtdItem.setIsRepeating(query.getColumn(colnum++));
				gtdItem.setRepeatFrom(std::string_view(query.getColumn(colnum++)));
				gtdItem.setRepeatSchedule(std::string_view(query.getColumn(colnum++)));
				if constexpr (std::is_same_v<Gtd_t, gtd::Project>) {
					gtdItem.setCompleteWithLast(static_cast<int>(query.getColumn(colnum++)));
				}

			}
            gtdItems.push_back(gtdItem);
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return gtdItems;
}

auto
importContexts(std::string_view pathname) {
	return importGtdItems<gtd::Context, std::vector<gtd::Context>>(pathname);
}

auto
importTasks(std::string_view pathname) {
	return importGtdItems<gtd::Task, std::vector<gtd::Task>>(pathname);
}

auto
importProjects(std::string_view pathname) {
	return importGtdItems<gtd::Project, std::vector<gtd::Project>>(pathname);
}

auto
importFolders(std::string_view pathname) {
	return importGtdItems<gtd::Folder, std::vector<gtd::Folder>>(pathname);
}

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
    auto contexts = importContexts("../sql_scripts/temp.db");
    auto tasks    = importTasks("../sql_scripts/temp.db");
    auto projects = importProjects("../sql_scripts/temp.db");
    auto folders  = importFolders("../sql_scripts/temp.db");

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
