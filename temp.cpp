#include <iomanip>
#include <iostream>
#include <filesystem>
#include <string_view>
#include <vector>
#include <ranges>

#include "GtdBase.hpp"
#include "GtdHelper.hpp"
#include "Project.hpp"
#include "Task.hpp"
#include "Context.hpp"
#include "ImplHelpers.hpp"

/// \brief Format the columns to same size
template <typename Gtd>
void
formatColumns( const std::vector<const Gtd>& gtdItems ) {
    static_assert(std::is_base_of_v<gtd::GtdBase, Gtd>); // ensure gtd object
    // Initialize longest string lengths
    int longestName   = 0;
    int longestStatus = 0;

    // 1. find longest row
    for ( const auto& gtdItem : gtdItems ) {
        // 1. find longest string for each field in all items
        longestName = (gtdItem.name().length() > longestName) ?
                          gtdItem.name().length() :
                          longestName;
        longestStatus = (gtdItem.statusStr().length() > longestStatus) ?
                            gtdItem.statusStr().length() :
                            longestStatus;
    }
    longestName++;
    longestStatus++;

    // 2. Format all fields for all records into equal column len
    std::cout << std::left << std::setw(longestName) << "TASK" << "| ";
    std::cout << std::left << std::setw(longestStatus) << "STATUS";
    std::cout << std::endl;
    std::cout << std::setfill('-') << std::left << std::setw(longestName + longestStatus + 1) << '-';
    std::cout << std::setfill(' ') << std::endl;
    using GtdTable = std::vector<std::vector<std::string_view>>;
    GtdTable rows(gtdItems.size());
    for ( const auto& gtdItem : gtdItems ) {
        std::cout << std::left << std::setw(longestName) << gtdItem.name() << "| ";
        std::cout << std::left << std::setw(longestStatus) << gtdItem.statusStr();
        std::cout << std::endl;
    }
}


// MAIN
/*****************************************************************************/
int
main() {
    const auto        dbPath = gtd::getDbConnPath();
    gtd::USMgrFactory usm;

    using gtd::GtdType;
    auto contexts = gtd::importContexts(dbPath, usm(GtdType::Context));
    auto folders  = gtd::importFolders(dbPath, usm(GtdType::Folder));
    auto tasks    = gtd::importTasks(dbPath, usm(GtdType::Task));
    auto projects = gtd::importProjects(dbPath, usm(GtdType::Project));

    // Add new Context and test
    const auto p_josh = std::make_unique<gtd::Context>(usm(GtdType::Context), "Josh");
    gtd::insertContext(dbPath, *p_josh);
    contexts.push_back(*p_josh);

    const auto p_danielleConcert = std::make_unique<gtd::Project>(usm(GtdType::Project), "Danielle's concert");
    p_danielleConcert->setDue("2023-12-05 18:00:00");
    gtd::insertProject(dbPath, *p_danielleConcert);
    projects.push_back(std::move(*p_danielleConcert));
    if ( p_danielleConcert ) {
        std::cout << "there is still a value in danielle concert\n";
    }
    p_danielleConcert->setContextId(5);
    p_danielleConcert->setProjectType(gtd::ProjectType::Sequential);
    p_danielleConcert->setCompleteWithLast(false);

    const auto p_buyStocking = std::make_unique<gtd::Task>(usm(GtdType::Task), "Buy christmas stocking");
    p_buyStocking->setDue("2023-12-05 16:00:00");
    gtd::insertTask(dbPath, *p_buyStocking);
    tasks.push_back(*p_buyStocking);
    p_buyStocking->setStatus(gtd::Status::Dropped);

    std::cout << "PROJECT STACK\n";
    const auto pUpdater = usm(GtdType::Project).getUpdateStack();
    std::cout << pUpdater->compose(projects) << std::endl;

    std::cout << "TASK STACK\n";
    const auto pTaskUpdater = usm(GtdType::Task).getUpdateStack();
    std::cout << pTaskUpdater->compose(tasks) << std::endl;
}
