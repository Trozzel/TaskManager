//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_FOLDER_HPP
#define GTD_FOLDER_HPP

#include <string>

namespace gtd {

class Folder {
private:
    std::string _folderName{};

    const Folder *_parent{nullptr};

public:
    explicit Folder(std::string folder = "New Folder", Folder* parent= nullptr);

    // GETTERS
    inline const Folder *getParent() const {
        return _parent;
    }

    inline std::string folderName() const {
        return _folderName;
    }

    inline std::string parentName() const {
        return _parent->_folderName;
    }

    // SETTERS
    inline void setParent(const Folder *parent = nullptr) {
        _parent = parent;
    }

    inline void setName(const std::string &folder) {
        _folderName = folder;
    }
};

} // namespace gtd

#endif//GTD_FOLDER_HPP
