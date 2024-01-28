//
// Created by George Ford on 1/9/24.
//

#ifndef GTD_CONCEPTS_HPP
#define GTD_CONCEPTS_HPP

#include <type_traits>

#include "GtdHelper.hpp"
//#include "GtdBase.hpp"
//#include "Context.hpp"
//#include "Folder.hpp"
//#include "Project.hpp"
//#include "Task.hpp"

template <typename Gtd_t>
concept cGtdBase = std::is_base_of_v<gtd::GtdBase, Gtd_t>;

template <typename Gtd_t>
concept cGtd = Gtd_t::gtd_category::constructible;

template<typename Gtd_t>
concept cContext = Gtd_t::gtd_category::gtd_type == gtd::GtdType::Context;

template<typename Gtd_t>
concept cFolder = Gtd_t::gtd_category::gtd_type == gtd::GtdType::Folder;

template <typename Gtd_t>
concept cCompletable = Gtd_t::gtd_category::completable;

template <typename Gtd_t>
concept cTask = Gtd_t::gtd_category::gtd_type == gtd::GtdType::Task;

template <typename Gtd_t>
concept cProject = Gtd_t::gtd_category::gtd_type == gtd::GtdType::Project;

#endif //GTD_CONCEPTS_HPP
