#include <gtest/gtest.h>
#include "delete_with_complex_condition.hpp"

namespace delete_with_complex_condition {

TEST(delete_with_complex_condition, test_query_generation) {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    std::vector<User> users = {
        {1, 17, "active"},
        {2, 20, "inactive"},
        {3, 30, "active"},
        {4, 15, "inactive"}
    };
    auto conn = sqlite::connect("test_db.sqlite");
    drop<User>(conn);
    create_table<User>(conn);
    insert(conn, users);
    delete_with_complex_condition();
    std::vector<User> remaining = sqlgen::read<std::vector<User>>(conn).value();
    ASSERT_EQ(remaining.size(), 1);
    EXPECT_EQ(remaining[0].id.value(), 3);
}

}