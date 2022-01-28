//
// Created by George Ford on 1/28/22.
//

#include "Context.hpp"
#include <utility>

using namespace std;

namespace gtd {
  // CTOR
  /****************************************************************************/
  Context::Context(std::string  task, Context* parent) :
    _taskName(std::move(task)), _parent(parent)
  {
      _created = dt::CTime::currentCTime();
      _modified = dt::CTime::currentCTime();
  }

  // COPY CTOR
  /****************************************************************************/
  Context::Context(const Context& other) :
    _taskName(other._taskName), _parent(other._parent)
  {
      _created = dt::CTime::currentCTime();
      _modified = dt::CTime::currentCTime();
  }

  // COPY ASSIGNMENT
  /****************************************************************************/
  Context& Context::operator= (const Context& other) {
      if (this != &other) {
          _taskName = other._taskName;
          _parent   = other._parent; // Make another reference to parent
          _created  = dt::CTime::currentCTime();
          _modified = dt::CTime::currentCTime();
      }
      return *this;
  }

  // MOVE CTOR
  /****************************************************************************/
  Context::Context(Context&& other)  noexcept :
    _taskName(std::move(other._taskName)),
    _parent(other._parent),
    _created(other._created),
    _modified(other._modified)
  {
  }

  // MOVE ASSIGNMENT
  /****************************************************************************/
  Context& Context::operator=(Context&& other) noexcept {
      if (this != &other) {
          _taskName = std::move(other._taskName);
          _parent   = other._parent;
          _created  = other._created;
          _modified = other._modified;
      }
      return *this;
  }

  // GETTERS
  /****************************************************************************/
  std::string Context::taskName() const {
      return _taskName;
  }
  dt::CTime Context::created() const {
      return _created;
  }
  dt::CTime Context::modified() const {
      return _modified;
  }
  std::string Context::parentName() const {
      return _parent->_taskName;
  }

  // SETTERS
  /****************************************************************************/
  void Context::setTaskName(const std::string& task) {
      _taskName = task;
  }
  void Context::setParent(const Context * parent) {
      _parent = parent;
  }

}// namespace gtd
