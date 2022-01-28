//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_APP_CONTEXT_H
#define GTD_APP_CONTEXT_H

#include <string>
#include <memory>

#include "CTime.hpp"

namespace gtd {
  class Context {
  private:
    std::string _taskName{};

    // A CONTEXT CAN ONLY HAVE CREATED AND UPDATED FIELDS
    dt::CTime _created{};
    dt::CTime _updated{};

    // A CONTEXT MAY HAVE A PARENT CONTEXT
    std::shared_ptr<Context> _parent {nullptr };

  public:
    // CTORS
    explicit Context(std::string  task, Context* parent=nullptr);
    explicit Context(std::string  task, std::shared_ptr<Context> parent=nullptr);

    // DTOR
    virtual ~Context() = default;

    // COPY CTOR AND ASSIGNMENT
    Context(const Context& other);
    Context& operator= (const Context& other);

    Context(Context&& other) noexcept;
    Context& operator= (Context&& other) noexcept;
  };
} // namespace gtd


#endif//GTD_APP_CONTEXT_H
