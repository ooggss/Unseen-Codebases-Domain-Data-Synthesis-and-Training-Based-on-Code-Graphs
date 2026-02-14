#include <gtest/gtest.h>
#include "like_pattern_matching.hpp"

namespace like_pattern_matching {

TEST(like_pattern_matching, test_query_generation) {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    std::vector<Product> products = {
        {1, "Apple"},
        {2, "Banana"},
        {3, "Orange"},
    };
    auto conn = sqlite::connect("test_db.sqlite").value();
    drop<Product>(conn);
    create_table<Product>(conn);
    insert(conn, products);
    std::vector<Product> result = like_pattern_matching::like_pattern_matching();
    EXPECT_TRUE(result.size() > 0);
    EXPECT_TRUE(result[0].name == "Apple");
}

}