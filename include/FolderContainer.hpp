//
// Created by George Ford on 12/19/23.
//

#ifndef FOLDERCONTAINER_HPP_
#define FOLDERCONTAINER_HPP_

#include <Folder.hpp>

#include "GtdBaseContainer.hpp"

namespace gtd {

class Folder;
using pFolder_t = std::unique_ptr<Folder>;

class FolderContainer final : public GtdContainer {
private:
    std::vector<pFolder_t>  _gtdItems{};

public:
    using value_type      = std::vector<pFolder_t>::value_type;
    using iterator        = std::vector<pFolder_t>::iterator;
    using const_iterator  = std::vector<pFolder_t>::const_iterator;
    using size_type       = std::vector<pFolder_t>::size_type;
    using difference_type = std::vector<pFolder_t>::difference_type;

    explicit FolderContainer(USMgr&);
    FolderContainer(const FolderContainer&) = delete;
    ~FolderContainer() override;

    FolderContainer&
        operator=(const FolderContainer&) = delete;

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
} // namespace gtd


#endif //FOLDERCONTAINER_HPP_
