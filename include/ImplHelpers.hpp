#ifndef IMPL_HELPERS_HPP_
#define IMPL_HELPERS_HPP_

#include <cstring>
#include <iterator>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <vector>

#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Statement.h"
#include "toml.hpp"
#include "SQLiteCpp/SQLiteCpp.h"

#include "GtdBase.hpp"
#include "Context.hpp"
#include "Task.hpp"
#include "Project.hpp"
#include "Folder.hpp"
#include "UpdateStack.hpp"

namespace gtd {

/// \brief get the name of the table to which the element belongs
template<typename Gtd_t>
constexpr const char*
tableName() noexcept {
	static_assert(std::is_base_of_v<gtd::GtdBase, Gtd_t>);
	if constexpr(std::is_same_v<Gtd_t, gtd::Project>) {
		return "projects";
	} else if constexpr(std::is_same_v<Gtd_t, gtd::Context>){
		return "contexts";
	} else if constexpr(std::is_same_v<Gtd_t, gtd::Folder>){
		return "folders";
	} else if constexpr(std::is_same_v<Gtd_t, gtd::Task>) {
		return "tasks";
	}
}

// INSERT RECORDS
/*****************************************************************************/

/// \brief Insert new Gtd item into database
template<typename Gtd_t>
std::string
getInsertStr(const Gtd_t& gtdItem) {
	static_assert(std::is_base_of_v<gtd::GtdBase, Gtd_t>);
	// Get table name
	static constexpr auto table = tableName<Gtd_t>();
	
	// Close statement for gtd::Context and gtd::Folder
	if constexpr (std::is_same_v<gtd::Context, Gtd_t> ||
				  std::is_same_v<gtd::Folder, Gtd_t>) {
		// Base Insert statement. queryStmt is updated based upon Gtd_t class
		return fmt::format(
				"INSERT INTO {table} (name, parentId, status, notes) "\
				"VALUES (\"{name}\", {parentId}, \"{status}\", {notes})", 
				fmt::arg("table", table), 
				fmt::arg("name", gtdItem.name()), 
				fmt::arg("parentId", (gtdItem.parentId() ? 
					std::to_string(gtdItem.parentId().value()) : "NULL")),
				fmt::arg("status", gtdItem.statusStr()), 
				fmt::arg("notes", (gtdItem.notes() ? 
					'"' + std::string(*gtdItem.notes()) + '"' : "NULL")));
	}
	// Create SELECT statement for gtd::Task
	else if constexpr (std::is_same_v<gtd::Task, Gtd_t>) {
		return fmt::format(
				"INSERT INTO {table} (name, parentId, status, notes, contextId, " \
							"projectId, flagged, deferred, due, isRepeating, "\
							"repeatFrom, repeatSchedule) "\
				"VALUES (\"{name}\", {parentId}, \"{status}\", {notes}, "\
							"{contextId}, {projectId}, {flagged}, {deferred}, "\
							"{due}, {isRepeating}, \"{repeatFrom}\", \"{repeatSchedule}\")",
				fmt::arg("table", table), 
				fmt::arg("name", gtdItem.name()), 
				fmt::arg("parentId", (gtdItem.parentId() ? 
					std::to_string(gtdItem.parentId().value()) : "NULL")),
				fmt::arg("status", gtdItem.statusStr()),
				fmt::arg("notes", (gtdItem.notes() ? 
					'"' + std::string(*gtdItem.notes()) + '"' : "NULL")),
				fmt::arg("contextId", (gtdItem.contextId() ? 
						std::to_string(*gtdItem.contextId()) : "NULL")),
				fmt::arg("projectId", (gtdItem.projectId() ?
						std::to_string(*gtdItem.contextId()) : "NULL")),
				fmt::arg("flagged", gtdItem.flagged()),
				fmt::arg("deferred", (gtdItem.deferredStr() ? 
						'"' + *gtdItem.deferredStr() + '"' : "NULL")),
				fmt::arg("due", (gtdItem.dueStr() ?
						'"' + *gtdItem.dueStr() + '"' : "NULL")),
				fmt::arg("isRepeating", gtdItem.isRepeating()),
				fmt::arg("repeatFrom", gtdItem.repeatFromStr()),
				fmt::arg("repeatSchedule", gtdItem.repeatSchedule()));
	}
	else if constexpr (std::is_same_v<gtd::Project, Gtd_t>) {
		return fmt::format(
				"INSERT INTO {table} (name, parentId, status, notes, contextId, "\
							"folderId, flagged, deferred, due, isRepeating, "\
							"repeatFrom, repeatSchedule, completeWithLast, "\
							"reviewSchedule) "\
				"VALUES (\"{name}\", {parentId}, \"{status}\", {notes}, "\
						"{contextId}, {folderId}, {flagged}, {deferred}, "\
						"{due}, {isRepeating}, \"{repeatFrom}\", \"{repeatSchedule}\", "\
						"{completeWithLast}, \"{reviewSchedule}\")",
				fmt::arg("table", table),
				fmt::arg("name", gtdItem.name()),
				fmt::arg("parentId", (gtdItem.parentId() ? 
					std::to_string(gtdItem.parentId().value()) : "NULL")),
				fmt::arg("status", gtdItem.statusStr()),
				fmt::arg("notes", (gtdItem.notes() ? 
					'"' + std::string(*gtdItem.notes()) + '"' : "NULL")),
				fmt::arg("contextId", (gtdItem.contextId() ?
					std::to_string(*gtdItem.contextId()) : "NULL")),
				fmt::arg("folderId", (gtdItem.folderId() ? 
					std::to_string(*gtdItem.folderId()) : "NULL")),
				fmt::arg("flagged", gtdItem.flagged()),
				fmt::arg("deferred", (gtdItem.deferredStr() ? 
						'"' + *gtdItem.deferredStr() + '"' : "NULL")),
				fmt::arg("due", (gtdItem.dueStr() ?
						'"' + *gtdItem.dueStr() + '"' : "NULL")),
				fmt::arg("isRepeating", gtdItem.isRepeating()),
				fmt::arg("repeatFrom", gtdItem.repeatFromStr()),
				fmt::arg("repeatSchedule", gtdItem.repeatSchedule()),
				fmt::arg("completeWithLast", gtdItem.completeWithLast()),
				fmt::arg("reviewSchedule", gtdItem.reviewSchedule()));
	}
	else {
		throw std::runtime_error("Not a valid Gtd type");
	}
}

/// Insert Gtd_t item into database
/// \param dbPath path to the SQLite database
/// \param gtdItem derivative of GtdBase
/// \return tuple<int, int>, where [0] is num insertions and [1] is new 
/// uniqueId
template<typename Gtd_t>
std::tuple<int, int>
insertGtdItem(std::string_view dbPath, Gtd_t& gtdItem) {
	static_assert(std::is_base_of_v<gtd::GtdBase, Gtd_t>);
	int res {0};
	uint64_t uniqueId {0};
	try {
		// Initiate db connections
		SQLite::Database db(dbPath, SQLite::OPEN_READWRITE);
		res = db.exec(getInsertStr<Gtd_t>(gtdItem));
		// Update the Gtd_t object to access it's newly assigned uniqueId
		gtdItem.setUniqueId(db.getLastInsertRowid());
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		throw(std::runtime_error(fmt::format("Error inserting {}", gtdItem.name())));
	}
	return {res, uniqueId};
}

/// \brief specialization of inserting Gtd item
std::tuple<int, int>
insertContext(std::string_view dbPath, gtd::Context& context);

std::tuple<int, int>
insertFolder(std::string_view dbPath, gtd::Folder& folder);

std::tuple<int, int>
insertTask(std::string_view dbPath, gtd::Task& task);

std::tuple<int, int>
insertProject(std::string_view dbPath, gtd::Project& project);

// IMPORT RECORDS
/*****************************************************************************/

/// \brief Get Gtd Items from db
template<typename Gtd_t, typename VectorGtd>
VectorGtd
importGtdItems(std::string_view dbPath, USMgr& updateStackMgr, const GtdType gtdType) {
	static_assert(std::is_base_of_v<gtd::GtdBase, Gtd_t>);
	static_assert(std::is_base_of_v<gtd::GtdBase, typename VectorGtd::value_type>);
	// Get table name
	std::remove_const_t<VectorGtd> gtdItems;

	const char* table = gtdTypeToStr(gtdType).data();
    try {
		// Initiate db connection
		const SQLite::Database db(dbPath);

		// Create SELECT statement
		//std::string queryStmt = "SELECT * FROM " + std::string(updateStackMgr.tableName());

		// Prepare beginning of sql statement
		constexpr size_t queryStmtSz = 100;
		char queryStmt[queryStmtSz] = "SELECT * FROM ";
		strncat(queryStmt, table, queryStmtSz);
        SQLite::Statement query(db, queryStmt);

		// Populate std::vector<Gtd_t> from database
        while(query.executeStep()) {
            constexpr bool dontUpdate = false;
			int colnum {0};
            Gtd_t gtdItem{updateStackMgr};
            gtdItem.setUniqueId(query.getColumn(colnum++).getInt64());
            gtdItem.setName(query.getColumn(colnum++).getString(), dontUpdate);
			if(!query.isColumnNull(colnum++)) {
				gtdItem.setParentId(query.getColumn(colnum - 1).getInt64(), dontUpdate);
			}
            gtdItem.setStatus(std::string_view(query.getColumn(colnum++).getString()), dontUpdate);
            gtdItem.setCreated(std::string_view(query.getColumn(colnum++).getString()), dontUpdate);
            gtdItem.setModified(std::string_view(query.getColumn(colnum++).getString()), dontUpdate);
			gtdItem.setNotes(query.getColumn(colnum++).getString(), dontUpdate);
			if constexpr(std::is_base_of_v<gtd::Completable, Gtd_t>) {
				if(!query.isColumnNull(colnum++)) {
					gtdItem.setContextId(query.getColumn(colnum - 1).getInt64(), dontUpdate);
				}
				if constexpr(std::is_same_v<Gtd_t, gtd::Task>) {
					if(!query.isColumnNull(colnum++)) {
						gtdItem.setProjectId(query.getColumn(colnum - 1).getInt64(), dontUpdate);
					}
				} else { // dealing with a gtd::Project
					if(!query.isColumnNull(colnum++)) {
						gtdItem.setFolderId(query.getColumn(colnum - 1).getInt64(), dontUpdate);
					}
				}
				gtdItem.setFlagged(query.getColumn(colnum++), dontUpdate);
				if(!query.isColumnNull(colnum++)) {
					gtdItem.setDeferred(std::string_view(query.getColumn(colnum - 1).getString()), dontUpdate);
				}
				if(!query.isColumnNull(colnum++)) {
					gtdItem.setDue(std::string_view(query.getColumn(colnum - 1).getString()), dontUpdate);
				}
				gtdItem.setIsRepeating(query.getColumn(colnum++).getInt(), dontUpdate);
				gtdItem.setRepeatFrom(std::string_view(query.getColumn(colnum++).getString()), dontUpdate);
				gtdItem.setRepeatSchedule(std::string_view(query.getColumn(colnum++).getString()), dontUpdate);
				if constexpr (std::is_same_v<Gtd_t, gtd::Project>) {
					gtdItem.setCompleteWithLast(query.getColumn(colnum++).getInt(), dontUpdate);
					gtdItem.setReviewSchedule(query.getColumn(colnum).getString(), dontUpdate);
				}

			}
            gtdItems.push_back(std::move(gtdItem));
        }
		if(gtdItems.empty()) {
			fmt::println("Did not import any items from table, '{}'", table);
		}

    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
		throw std::runtime_error(fmt::format("error in importing from Sqlite table, {}", table));
    }
    return gtdItems;
}

std::vector<Context>
importContexts(std::string_view pathname, USMgr&); 

std::vector<Task>
importTasks(std::string_view pathname, USMgr&); 

std::vector<Project>
importProjects(std::string_view pathname, USMgr&); 

std::vector<Folder>
importFolders(std::string_view pathname, USMgr&); 

} // namespace gtd
#endif // IMPL_HELPERS_HPP_
