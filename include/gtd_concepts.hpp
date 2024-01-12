//
// Created by George Ford on 1/9/24.
//

#ifndef GTD_CONCEPTS_HPP
#define GTD_CONCEPTS_HPP

#include <type_traits>

#include "GtdBase.hpp"
#include "Completable.hpp"
#include "Task.hpp"
#include "Project.hpp"

template <typename Gtd_t>
concept cGtdBase = std::is_base_of_v<gtd::GtdBase, Gtd_t>;

template <typename Gtd_t>
concept cCompletable = std::is_base_of_v<gtd::Completable, Gtd_t>;

template <typename Gtd_t>
concept cTask = std::is_same_v<gtd::Task, Gtd_t>;

template <typename Gtd_t>
concept cProject = std::is_same_v<gtd::Project, Gtd_t>;

#endif //GTD_CONCEPTS_HPP
