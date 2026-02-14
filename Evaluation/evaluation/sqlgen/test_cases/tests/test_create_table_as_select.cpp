#include <gtest/gtest.h>
#include "create_table_as_select.hpp"

namespace create_table_as_select {

TEST(create_table_as_select, test_query_generation) {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    auto conn = sqlite::connect("test_db.sqlite").value();
    std::vector<Source> sources = {{1, 100}, {2, 200}, {3, 300}};
    drop<Source>(conn);
    drop<Target>(conn);
    create_table<Source>(conn);
    insert(conn, sources);
    std::vector<Target> targets = create_table_as_select::create_table_as_select();
    EXPECT_EQ(targets.size(), 2);
    EXPECT_EQ(targets[0].value, 200);
    EXPECT_EQ(targets[1].value, 300);
}

}