//
// Created by George Ford on 1/12/24.
//
#include <cstddef>
#include <gtest/gtest.h>

#include "GtdContainer.hpp"
#include "GtdHelper.hpp"
#include "Task.hpp"

using namespace gtd;

auto& contexts = gtd::GtdContainer<gtd::Context>::initFromDb();
auto& folders  = gtd::GtdContainer<gtd::Folder>::initFromDb();
auto& projects = gtd::GtdContainer<gtd::Project>::initFromDb();
auto& tasks    = gtd::GtdContainer<gtd::Task>::initFromDb();

const size_t c_sz_init = contexts->size();
const size_t f_sz_init = folders->size();
const size_t p_sz_init = projects->size();
const size_t t_sz_init = tasks->size();

TEST(GtdContainerTest, TableName) {
	EXPECT_EQ(contexts->tableName(), "contexts");
	EXPECT_EQ(folders->tableName(), "folders");
	EXPECT_EQ(projects->tableName(), "projects");
	EXPECT_EQ(tasks->tableName(), "tasks");
}

TEST(GtdContainerTest, CreateElement) {
	const char* c1 = "c1";
	const char* f1 = "f1";
	const char* p1 = "p1";
	const char* t1 = "t1";
	contexts->create(contexts, c1);
	folders->create(folders,   f1);
	projects->create(projects, p1);
	tasks->create(tasks,       t1);
	
	EXPECT_EQ(contexts->size(), c_sz_init + 1);
	EXPECT_EQ(folders->size(), f_sz_init + 1);
	EXPECT_EQ(projects->size(), p_sz_init + 1);
	EXPECT_EQ(tasks->size(), t_sz_init + 1);

	EXPECT_EQ(contexts->back().name(), c1);
	EXPECT_EQ(contexts->back().name(), f1);
	EXPECT_EQ(contexts->back().name(), p1);
	EXPECT_EQ(contexts->back().name(), t1);
}

TEST(GtdContainerTest, DeleteElement) {
	contexts->erase(contexts->back());
	folders->erase(folders->back());
	projects->erase(projects->back());
	tasks->erase(tasks->back());

	EXPECT_EQ(contexts->size(), c_sz_init);
	EXPECT_EQ(contexts->size(), f_sz_init);
	EXPECT_EQ(contexts->size(), p_sz_init);
	EXPECT_EQ(contexts->size(), t_sz_init);
}

TEST(GtdContainerTest, AttachGtdItem) {
	auto c1 = gtd::Context(nullptr, "name");
	auto f1 = gtd::Folder(nullptr, "name");
	auto p1 = gtd::Project(nullptr, "name");
	auto t1 = gtd::Task(nullptr, "name");

	contexts->attach(c1);
	folders->attach(f1);
	projects->attach(p1);
	tasks->attach(t1);

	EXPECT_EQ(contexts->size(), c_sz_init + 1);
	EXPECT_EQ(folders->size(), f_sz_init + 1);
	EXPECT_EQ(projects->size(), p_sz_init + 1);
	EXPECT_EQ(tasks->size(), t_sz_init + 1);
}

TEST(GtdContainerTest, TrackSharedPtrCount) {
    EXPECT_EQ(contexts.use_count(), 1);
    EXPECT_EQ(folders.use_count(), 1);
    EXPECT_EQ(projects.use_count(), 1);
    EXPECT_EQ(tasks.use_count(), 1);
}

auto
main( int argc, char* argv[] ) -> int {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
