#include <gtest/gtest.h>
#include "read_to_select_from_usage.hpp"

namespace read_to_select_from_usage {

TEST(read_to_select_from_usage, test_query_generation) {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    auto conn = sqlite::connect("test_db.sqlite").value();
    drop<User>(conn);
    create_table<User>(conn);
    std::vector<User> users = {
        {1, "Alice", 20},
        {2, "Bob", 25},
        {3, "Charlie", 30},
        {4, "David", 35},
        {5, "Eve", 40},
        {6, "Frank", 45},
        {7, "Grace", 50},
        {8, "Heidi", 55},
        {9, "Ivan", 60},
        {10, "Judy", 65},
        {11, "Kevin", 70},
        {12, "Lily", 75},
    };
    insert(conn, users);
    std::vector<User> result = read_to_select_from_usage();
    ASSERT_EQ(result.size(), 10);
}

}