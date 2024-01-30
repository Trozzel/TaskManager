#ifndef GTDSQLITE_HPP_
#define GTDSQLITE_HPP_

#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Exception.h"
#include "SQLiteCpp/SQLiteCpp.h"
#include "GtdHelper.hpp"
#include "SQLiteCpp/Statement.h"
#include "fmt/base.h"
#include "gtd_concepts.hpp"
#include <memory>

// LOAD ITEMS FROM DATABASE
/*****************************************************************************/
namespace gtd {
template<typename Gtd_t>
class GtdContainer;


template <cGtd Gtd_t>
void
loadFromDb(std::shared_ptr<GtdContainer<Gtd_t>>& gtdItems) {
    try {
        auto               db        = SQLite::Database(gtd::getDbConnPath());
        const gtd::GtdType gtdType   = Gtd_t::gtd_category::gtd_type;
        const std::string  tableName = gtd::gtdTypeToTableName(gtdType);
        const auto         statement = fmt::format("SELECT * FROM {};", tableName);

        SQLite::Statement query(db, statement);
        constexpr bool    dontUpdate = false;
        while ( query.executeStep() ) {
            int colnum = 0;
            // NOTE: gtdItem invalidated after reallocation
            Gtd_t& gtdItem = gtdItems->create(gtdItems, "");
            gtdItem.setUniqueId(query.getColumn(colnum++).getInt64());
            gtdItem.setName(query.getColumn(colnum++).getString(), dontUpdate);
            if ( !query.isColumnNull(colnum) ) {
                gtdItem.setParentId(query.getColumn(colnum).getInt64(), dontUpdate);
            }
            ++colnum;
            gtdItem.setStatus(query.getColumn(colnum++).getString(), dontUpdate);
            gtdItem.setCreated(query.getColumn(colnum++).getString());
            gtdItem.setModified(query.getColumn(colnum++).getString());
            if ( !query.isColumnNull(colnum) ) {
                gtdItem.setNotes(query.getColumn(colnum).getString(), dontUpdate);
            }
            ++colnum;
            // POPULATE COMPLETABLE
            /*****************************************************************/
            if constexpr ( std::is_base_of_v<gtd::Completable, Gtd_t> ) {
                if ( !query.isColumnNull(colnum) ) {
                    gtdItem.setContextId(query.getColumn(colnum).getInt64(), dontUpdate);
                }
                ++colnum;
                if constexpr ( std::is_same_v<gtd::Task, Gtd_t> ) {
                    if ( !query.isColumnNull(colnum) ) {
                        gtdItem.setProjectId(query.getColumn(colnum).getInt64(), dontUpdate);
                    }
                    ++colnum;
                }
                else if ( std::is_same_v<gtd::Project, Gtd_t> ) {
                    if ( !query.isColumnNull(colnum) ) {
                        gtdItem.setFolderId(query.getColumn(colnum).getInt64(), dontUpdate);
                    }
                    ++colnum;
                }
                gtdItem.setFlagged(query.getColumn(colnum++).getInt(), dontUpdate);
                if ( !query.isColumnNull(colnum) ) {
                    gtdItem.setDeferred(query.getColumn(colnum).getString(), dontUpdate);
                }
                ++colnum;
                if ( !query.isColumnNull(colnum) ) {
                    gtdItem.setDue(query.getColumn(colnum).getString(), dontUpdate);
                }
                ++colnum;
                gtdItem.setIsRepeating(query.getColumn(colnum++).getInt(), dontUpdate);
                gtdItem.setRepeatFrom(query.getColumn(colnum++).getString(), dontUpdate);
                gtdItem.setRepeatSchedule(query.getColumn(colnum++).getString(), dontUpdate);
                if constexpr ( std::is_same_v<gtd::Task, Gtd_t> ) {
                    gtdItem.setTaskType(query.getColumn(colnum++).getString(), dontUpdate);
                }
                else if ( std::is_same_v<gtd::Project, Gtd_t> ) {
					gtdItem.setCompleteWithLast(query.getColumn(colnum++).getInt(), dontUpdate);
                    gtdItem.setReviewSchedule(query.getColumn(colnum++).getString(), dontUpdate);
                    gtdItem.setProjectType(query.getColumn(colnum).getString(), dontUpdate);
                }
            }
        }
    }
    catch ( SQLite::Exception& e ) {
        fmt::print(stderr, "{}\n", e.what());
        throw std::runtime_error(e.what());
    }
}
template<cGtd Gtd_t>
std::string
getInsertStr(const Gtd_t& gtdItem) {
	// Get table name
	static constexpr auto table = Gtd_t::gtd_category::table_name;
	
	// Close statement for gtd::Context and gtd::Folder
	if constexpr (cContext<Gtd_t> || cFolder<Gtd_t>) {
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
	else if constexpr (cTask<Gtd_t>) {
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
						std::to_string(*gtdItem.projectId()) : "NULL")),
				fmt::arg("flagged", gtdItem.flagged()),
				fmt::arg("deferred", (gtdItem.deferredStr() ? 
						'"' + *gtdItem.deferredStr() + '"' : "NULL")),
				fmt::arg("due", (gtdItem.dueStr() ?
						'"' + *gtdItem.dueStr() + '"' : "NULL")),
				fmt::arg("isRepeating", gtdItem.isRepeating()),
				fmt::arg("repeatFrom", gtdItem.repeatFromStr()),
				fmt::arg("repeatSchedule", gtdItem.repeatSchedule()));
	}
	else if constexpr (cProject<Gtd_t>) {
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

template<cGtd Gtd_t>
unique_id_t
insertRecord( Gtd_t& gtdItem ) {
	try {
		// Initiate db connections
		SQLite::Database db(getDbConnPath(), SQLite::OPEN_READWRITE);
		db.exec(getInsertStr<Gtd_t>(gtdItem));
		return db.getLastInsertRowid();
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		throw(std::runtime_error(fmt::format("Error inserting {}", gtdItem.name())));
	}
}

template<cGtd Gtd_t>
int
removeRecord( const Gtd_t& gtdItem ) {
	if (!gtdItem.uniqueId()) {
		fmt::println("WARNING: no uniqueId for {}", gtdItem.name());
		return 0;
	}
	try {
		auto db = SQLite::Database(getDbConnPath(), SQLite::OPEN_READWRITE);
		auto qry = SQLite::Statement(db, fmt::format("DELETE FROM {} WHERE uniqueId = {}",
					Gtd_t::gtd_category::table_name, *gtdItem.uniqueId()));
		int numRemoved = qry.exec();
		if(numRemoved == 0) {
			fmt::println("WARNING: record, '{}', uniqueId: {}, was not deleted",
					gtdItem.name(), *gtdItem.uniqueId());
		}
		return numRemoved;
	}
	catch (SQLite::Exception& e) {
		fmt::println(stderr, "Error removing element, {}, uniqueId: {}", 
				gtdItem.name(), *gtdItem.uniqueId());
		throw SQLite::Exception(e.what());
	}
}

} // namespace gtd

#endif // GTDSQLITE_HPP_
