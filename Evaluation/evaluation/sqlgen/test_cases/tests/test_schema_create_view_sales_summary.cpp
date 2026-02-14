#include <gtest/gtest.h>
#include <vector>
#include <string>

#include "schema_create_view_sales_summary.hpp"

namespace schema_create_view_sales_summary {

/**
 * Test Case: Test creation of SalesSummary view
 * 
 * Test Scenario:
 * - Create Product and Sale tables and insert data
 * - Call create_view_sales_summary
 * - Verify view exists by selecting from it
 * - Verify aggregated results
 */
TEST(sqlite, create_view_sales_summary) {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  // Cleanup
  auto conn = sqlite::connect("test_db.sqlite").value();
  drop<Product>(conn);
  drop<Sale>(conn);
  drop<SalesSummary>(conn);

  // 1. Create tables and insert data
  create_table<Product>(conn);
  create_table<Sale>(conn);

  Product p1{.product_id = 1, .name = "Widget A", .price = 10.0, .stock = 100};
  Product p2{.product_id = 2, .name = "Widget B", .price = 20.0, .stock = 100};
  insert(conn, std::vector{p1, p2});

  Sale s1{.sale_id = 1, .product_id = 1, .quantity = 2, .amount = 20.0};
  Sale s2{.sale_id = 2, .product_id = 1, .quantity = 3, .amount = 30.0};
  Sale s3{.sale_id = 3, .product_id = 2, .quantity = 1, .amount = 20.0};
  insert(conn, std::vector{s1, s2, s3});

  // 2. Call create_view_sales_summary
  // bool success = create_view_sales_summary();
  // EXPECT_TRUE(success);
  auto result = create_view_sales_summary();

  // Widget A: total quantity 5, total revenue 50.0
  // Widget B: total quantity 1, total revenue 20.0
  // Note: order depends on query, we ordered by product_name
  ASSERT_EQ(result.size(), 2);
  
  EXPECT_EQ(result[0].product_name, "Widget A");
  EXPECT_EQ(result[0].total_quantity, 5);
  EXPECT_EQ(result[0].total_revenue, 50.0);

  EXPECT_EQ(result[1].product_name, "Widget B");
  EXPECT_EQ(result[1].total_quantity, 1);
  EXPECT_EQ(result[1].total_revenue, 20.0);
}

}  // namespace schema_create_view_sales_summary
