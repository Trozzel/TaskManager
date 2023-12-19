//
// Created by George Ford on 12/11/23.
//

#ifndef DBBASE_HPP_
#define DBBASE_HPP_
#include <string>
#include <string_view>


class DbBase {
protected:
    std::string_view            _uri;

public:
    explicit DbBase(std::string_view uri);
    virtual ~DbBase() = 0;

	virtual int exec(std::string_view queries) = 0;
};



#endif //DBBASE_HPP_
