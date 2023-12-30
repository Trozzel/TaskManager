//
// Created by George Ford on 12/19/23.
//

#ifndef PROJECTCONTAINER_HPP
#define PROJECTCONTAINER_HPP

#include "CompleteableContainer.hpp"

namespace gtd {

class Project;
using pProject_t = std::unique_ptr<Completable>;

class ProjectContainer final : public CompleteableContainer {
private:
    std::vector<pProject_t>     _gtdItems;

public:
    using value_type      = std::vector<pProject_t>::value_type;
    using iterator        = std::vector<pProject_t>::iterator;
    using const_iterator  = std::vector<pProject_t>::const_iterator;
    using size_type       = std::vector<pProject_t>::size_type;
    using difference_type = std::vector<pProject_t>::difference_type;

    explicit ProjectContainer(USMgr&);
    ProjectContainer(const ProjectContainer&);
    ~ProjectContainer() override;

    ProjectContainer&
        operator=(const ProjectContainer&);

    [[nodiscard]] const std::string&
    tableName() const override;

    [[nodiscard]]
    auto
    begin() override;

    [[nodiscard]]
    auto
    cbegin() const override;

    [[nodiscard]]
    auto
    end() override;

    [[nodiscard]]
    auto
    cend() const override;
};

}

#endif //PROJECTCONTAINER_HPP
