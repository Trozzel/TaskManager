//
// Created by George Ford on 1/28/22.
//

#include "Context.h"

#include <utility>

using namespace std;

namespace gtd {

  // CTOR WITH RAW POINTER
  /****************************************************************************/
  Context::Context(std::string  task, Context* parent) :
    _taskName(std::move(task)), _parent(parent)
  {
    _created = dt::CTime::currentCTime();
    _updated = dt::CTime::currentCTime();
  }

  // CTOR WITH SHARED POINTER
  /****************************************************************************/
  Context::Context(string  task, std::shared_ptr<Context> parent) :
    _taskName(std::move(task)), _parent(std::move(parent))
  {
    _created = dt::CTime::currentCTime();
    _updated = dt::CTime::currentCTime();
  }

  // COPY CTOR
  /****************************************************************************/
  Context::Context(const Context& other) :
    _taskName(other._taskName), _parent(other._parent)
  {
    _created = dt::CTime::currentCTime();
    _updated = dt::CTime::currentCTime();
  }

  // COPY ASSIGNMENT
  /****************************************************************************/
  Context& Context::operator= (const Context& other) {
    if (this != &other) {
      _taskName = other._taskName;
      _parent   = other._parent; // Make another reference to parent
      _created  = dt::CTime::currentCTime();
      _updated  = dt::CTime::currentCTime();
    }
    return *this;
  }

  // MOVE CTOR
  /****************************************************************************/
  Context::Context(Context&& other)  noexcept {
    _taskName = std::move(other._taskName);
    _parent   = std::move(other._parent);
    _created  = other._created;
    _updated  = other._updated;
  }

  // MOVE ASSIGNMENT
  /****************************************************************************/
  Context& Context::operator=(Context&& other) {
    return <#initializer #>;
  }
}// namespace gtd
