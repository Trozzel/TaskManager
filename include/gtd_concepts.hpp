//
// Created by George Ford on 1/9/24.
//

#ifndef GTD_CONCEPTS_HPP
#define GTD_CONCEPTS_HPP

#include <type_traits>

#include "GtdHelper.hpp"
#include "GtdBase.hpp"
#include "Context.hpp"
#include "Folder.hpp"
#include "Project.hpp"
#include "Task.hpp"

template <typename Gtd_t>
concept cGtdBase = std::is_base_of_v<gtd::GtdBase, Gtd_t>;

template <typename Gtd_t>
concept cGtd = 
	std::is_same_v<gtd::Context, Gtd_t> ||
	std::is_same_v<gtd::Folder,  Gtd_t> ||
	std::is_same_v<gtd::Project, Gtd_t> ||
	std::is_same_v<gtd::Task,    Gtd_t>;

template <typename Gtd_t>
concept cCompletable = std::is_base_of_v<gtd::Completable, Gtd_t>;

template <typename Gtd_t>
concept cTask = std::is_same_v<gtd::Task, Gtd_t>;

template <typename Gtd_t>
concept cProject = std::is_same_v<gtd::Project, Gtd_t>;

#endif //GTD_CONCEPTS_HPP
