//
// Created by George Ford on 1/12/24.
//
#include <gtest/gtest.h>

#include "GtdContainer.hpp"

using namespace gtd;

const auto contexts = std::make_shared<GtdContainer<Context>>();
auto&      c1       = contexts->create(contexts, "c1");
auto&      c2       = contexts->create(contexts, "c2");
auto&      c3       = contexts->create(contexts, "c3");

TEST(GtdContainerTest, TrackSharedPtrCount) {
    EXPECT_EQ(contexts.use_count(), 4);
    EXPECT_EQ(contexts->size(), 3);
}

TEST(GtdContainerTest, DeleteGtdItem) {
    fmt::println("c2.name(): {}", c2.name());
    contexts->erase(c2);
    EXPECT_EQ(contexts.use_count(), 3);
    EXPECT_EQ(contexts->size(), 2);
}

auto
main( int argc, char* argv[] ) -> int {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
