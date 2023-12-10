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
#include <memory>
#include <stdexcept>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>
#include <ranges>
	
#include "GtdBase.hpp"
#include "GtdHelper.hpp"
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
	auto dbPath = gtd::getDbConnPath();

	// Initiate the DB update managers
	auto contextUpdater = gtd::USMgr("contexts"); 
	auto folderUpdater = gtd::USMgr("folders"); 
	auto taskUpdater = gtd::USMgr("tasks");     
	auto projectUpdater = gtd::USMgr("projects");

	auto contexts = gtd::importContexts(dbPath, contextUpdater);
    auto folders  = gtd::importFolders(dbPath, folderUpdater);
    auto tasks    = gtd::importTasks(dbPath, taskUpdater);
    auto projects = gtd::importProjects(dbPath, projectUpdater);

	// Get parents from all tasks
	//auto childToParent = tasks 
	//	| std::views::filter([](const auto& task) {
	//			return task.parentId() != std::nullopt;
	//			})
	//	| std::views::transform([&tasks](const auto& task) {
	//			return std::make_pair(task, *getParent_it(task, tasks));
	//			});
	//
	//for(const auto& p2c : childToParent) {
	//	std::cout << p2c.first.name() << " -> " << p2c.second.name() << std::endl;
	//	std::cout << "notes: " << *p2c.first.notes() << std::endl;
	//}

	// Add new Context and test
	constexpr bool update     = true;
	constexpr bool dontUpdate = false;
	std::unique_ptr<gtd::Context> p_josh = std::make_unique<gtd::Context>(contextUpdater, "Josh");
	auto res = gtd::insertContext(dbPath, *p_josh);
	contexts.push_back(*p_josh);
	//std::cout << "Joshua's new uniqueId: " << *(p_josh->uniqueId()) << std::endl;

	auto p_danielleConcert = std::make_unique<gtd::Project>(projectUpdater, "Danielle's concert");
	p_danielleConcert->setDue("2023-12-05 18:00:00", dontUpdate);
	res = gtd::insertProject(dbPath, *p_danielleConcert);
	projects.push_back(*p_danielleConcert);
	p_danielleConcert->setContextId(5, update);
	p_danielleConcert->setProjectType(gtd::ProjectType::Sequential, update);
	p_danielleConcert->setCompleteWithLast(false, update);

	auto p_buyStocking = std::make_unique<gtd::Task>(taskUpdater, "Buy christmas stocking");
	p_buyStocking->setDue("2023-12-05 16:00:00", dontUpdate);
	res = gtd::insertTask(dbPath, *p_buyStocking);
	tasks.push_back(*p_buyStocking);
	p_buyStocking->setStatus(gtd::Status::Dropped, update);

	auto pUpdater = projectUpdater.getUpdateStack();
	std::cout << pUpdater->compose() << std::endl;
}
