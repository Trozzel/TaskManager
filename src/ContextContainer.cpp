//
// Created by George Ford on 12/19/23.
//

#include "ContextContainer.hpp"
#include "Context.hpp"

namespace gtd {
ContextContainer::ContextContainer( USMgr& usm ) :
    GtdBaseContainer(usm)
{
}

ContextContainer::~ContextContainer() = default;

const std::string&
ContextContainer::tableName() const {
    const static std::string table = "contexts";
    return table;
}

bool
ContextContainer::importAllFromDb() {
    try {
        std::string_view query{"SELECT * FROM contexts;"};
        while ( _dbCon->executeStep() ) {}
    }
    catch ( std::exception& e ) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw std::runtime_error("Error importing contexts");
    }
}

auto
ContextContainer::begin() {
    return _gtdItems.begin();
}

auto
ContextContainer::cbegin() const {
    return _gtdItems.cbegin();
}

auto
ContextContainer::end() {
    return _gtdItems.end();
}

auto
ContextContainer::cend() const {
    return _gtdItems.cend();
}
} // namespace gtd
