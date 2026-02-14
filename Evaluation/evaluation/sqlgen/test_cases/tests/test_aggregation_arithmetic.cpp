#include <gtest/gtest.h>
#include "aggregation_arithmetic.hpp"

namespace aggregation_arithmetic {

TEST(aggregation_arithmetic, test_query_generation) {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    auto conn = sqlite::connect("test_db.sqlite").value();
    drop<Product>(conn);
    create_table<Product>(conn);

    std::vector<Product> products = {
        {1, 100.0},
        {2, 200.0},
        {3, 300.0}
    };
    insert(conn, products);

    double result = aggregation_arithmetic();
    EXPECT_EQ(result, 210.0);
}

}