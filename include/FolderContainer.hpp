//
// Created by George Ford on 12/19/23.
//

#ifndef FOLDERCONTAINER_HPP_
#define FOLDERCONTAINER_HPP_

#include "GtdBaseContainer.hpp"

namespace gtd {

class Folder;
using pFolder_t = std::unique_ptr<Folder>;

class FolderContainer final : public GtdBaseContainer {
private:
    std::vector<pFolder_t>  _gtdItems{};

public:
    explicit FolderContainer(USMgr&);
    ~FolderContainer() override;

    [[nodiscard]] std::string
    tableName() const override;
};
} // namespace gtd


#endif //FOLDERCONTAINER_HPP_
