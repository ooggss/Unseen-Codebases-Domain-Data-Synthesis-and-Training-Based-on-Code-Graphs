#include <gtest/gtest.h>
#include "get_top_products.hpp"

namespace get_top_products {

TEST(sqlite, get_top_products) {
  using namespace sqlgen;
  auto conn = sqlite::connect("test_db.sqlite").value();
  drop<Product>(conn);
  drop<Sales>(conn);
  create_table<Product>(conn);
  create_table<Sales>(conn);

  insert(conn, std::vector<Product>{{1, "A", "C1", 10.0}, {2, "B", "C2", 20.0}, {3, "C", "C1", 5.0}});
  insert(conn, std::vector<Sales>{{1, 1, 2, sqlgen::Date{"2024-01-01"}},
                                  {2, 2, 4, sqlgen::Date{"2024-01-02"}},
                                  {3, 3, 20, sqlgen::Date{"2024-01-03"}}});

  auto rows = get_top_products(2);
  ASSERT_EQ(rows.size(), 2);
  EXPECT_EQ(rows[0].total_sales, 100.0);
  EXPECT_EQ(rows[1].total_sales, 80.0);
}

}  // namespace get_top_products

