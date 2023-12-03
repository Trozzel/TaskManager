#ifndef __IMPL_HELPERS_HPP__
#define __IMPL_HELPERS_HPP__

#include <string_view>
#include <vector>

#include <toml.hpp>
#include "SQLiteCpp/SQLiteCpp.h"
#include "Context.hpp"
#include "Task.hpp"
#include "Project.hpp"
#include "Folder.hpp"

namespace gtd {

// Read from database
/*****************************************************************************/

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

std::vector<Context>
importContexts(std::string_view pathname); 

std::vector<Task>
importTasks(std::string_view pathname); 

std::vector<Project>
importProjects(std::string_view pathname); 

std::vector<Folder>
importFolders(std::string_view pathname); 

// Create new records in db
/*****************************************************************************/


} // namespace gtd
#endif //__IMPL_HELPERS__
