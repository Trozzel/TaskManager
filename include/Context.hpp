//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_APP_CONTEXT_HPP
#define GTD_APP_CONTEXT_HPP

#include <string>

#include "CTime.hpp"

namespace gtd {

class Context {
private:
    std::string _taskName{};

    // A CONTEXT CAN ONLY HAVE CREATED AND UPDATED FIELDS
    dt::CTime _created{};
    dt::CTime _modified{};

    // A CONTEXT MAY HAVE A PARENT CONTEXT
    const Context* _parent { nullptr };

public:
    // CTORS
    explicit Context(std::string  task, Context* parent=nullptr);

    // DTOR
    virtual ~Context() = default;

    // COPY CTOR AND ASSIGNMENT
    Context(const Context& other);
    Context& operator= (const Context& other);

    Context(Context&& other) noexcept;
    Context& operator= (Context&& other) noexcept;

    // GETTERS
    [[nodiscard]] inline std::string taskName() const;
    [[nodiscard]] inline dt::CTime created()    const;
    [[nodiscard]] inline dt::CTime modified()   const;
    [[nodiscard]] std::string parentName()      const;

    // SETTERS
    void setTaskName(const std::string& task);
    void setParent(const Context * parent=nullptr);
};

} // namespace gtd


#endif//GTD_APP_CONTEXT_HPP
