#include <gtest/gtest.h>
#include "in_operator_usage.hpp"

namespace in_operator_usage {

TEST(in_operator_usage, test_query_generation) {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    auto conn = sqlite::connect("test_db.sqlite").value();
    std::vector<Status> status = {
        {1, 1},
        {2, 2},
        {3, 3},
        {4, 4},
    };
    drop<Status>(conn);
    create_table<Status>(conn);
    insert(conn, status);
    auto rows = in_operator_usage();
    ASSERT_GE(rows.size(), 3);
}

}