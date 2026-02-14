#include <gtest/gtest.h>
#include "order_by_descending.hpp"

namespace order_by_descending {

TEST(order_by_descending, test_query_generation) {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    std::vector<Score> scores = {
        {1, 90},
        {2, 80},
        {3, 100},
    };
    auto conn = sqlite::connect("test_db.sqlite").value();
    drop<Score>(conn);
    create_table<Score>(conn);
    insert(conn, scores);
    std::vector<Score> rows = order_by_descending();
    EXPECT_TRUE(rows.size() > 0);
    EXPECT_EQ(rows[0].id.value(), 3);
    EXPECT_EQ(rows[1].id.value(), 1);
    EXPECT_EQ(rows[2].id.value(), 2);
}

}