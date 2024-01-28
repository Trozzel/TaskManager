#include "GtdSqlite.hpp"
#include "gtd_concepts.hpp"

// LOAD ITEMS FROM DATABASE
/*****************************************************************************/
namespace gtd {

template <cGtd Gtd_t>
std::vector<Gtd_t>
loadFromDb() {
    auto gtdItems = gtd::GtdContainer<Gtd_t>();
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
            Gtd_t& gtdItem = gtdItems.create(gtdItems, "");
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

    return gtdItems;
}

} // namespace gtd
#endif // GTDSQLITE_HPP_
