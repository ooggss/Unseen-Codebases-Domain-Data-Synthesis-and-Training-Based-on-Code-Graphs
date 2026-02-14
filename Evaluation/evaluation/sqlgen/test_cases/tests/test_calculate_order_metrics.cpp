#include <gtest/gtest.h>
#include <sqlgen/sqlite.hpp>
#include "calculate_order_metrics.hpp"

using namespace calculate_order_metrics;

TEST(sqlite, CalculateOrderMetrics) {
  using namespace sqlgen;
  using namespace sqlgen::literals;
  
  std::vector<OrderItem> items = {
      {1, 101, 201, 100.0, 5, 10.0, 5.0}, // Normal item
      {2, 101, 202, 50.0, 12, std::nullopt, std::nullopt}, // Null discount/tax, modulo test (12 % 10 = 2)
      {3, 102, 203, 200.0, 20, 20.0, std::nullopt}, // Null tax, modulo test (20 % 10 = 0)
      {4, 103, 204, 75.0, 1, std::nullopt, 10.0} // Null discount
  };
  auto conn = sqlite::connect("test_db.sqlite")
    .and_then(drop<OrderItem> | if_exists)
    .and_then(create_table<OrderItem>)
    .and_then(insert(items))
    .value();

  auto metrics = calculate_order_metrics_impl();

  ASSERT_EQ(metrics.size(), 4);

  const auto& m1 = metrics[0];
  EXPECT_EQ(m1.item_id, 1);
  EXPECT_DOUBLE_EQ(m1.gross_total, 500.0);
  EXPECT_DOUBLE_EQ(m1.discounted_total, 450.0);
  EXPECT_DOUBLE_EQ(m1.final_total, 472.5);
  EXPECT_DOUBLE_EQ(m1.unit_cost, 100.0);
  EXPECT_EQ(m1.quantity_group, 5);
  EXPECT_DOUBLE_EQ(m1.estimated_profit, 30.0);
  EXPECT_DOUBLE_EQ(m1.discount_rate, 10.0);
  EXPECT_DOUBLE_EQ(m1.tax_rate, 5.0);

  const auto& m2 = metrics[1];
  EXPECT_EQ(m2.item_id, 2);
  EXPECT_DOUBLE_EQ(m2.gross_total, 600.0);
  EXPECT_DOUBLE_EQ(m2.discounted_total, 600.0);
  EXPECT_DOUBLE_EQ(m2.final_total, 600.0);
  EXPECT_DOUBLE_EQ(m2.unit_cost, 50.0);
  EXPECT_EQ(m2.quantity_group, 2);
  EXPECT_DOUBLE_EQ(m2.estimated_profit, 15.0);
  EXPECT_DOUBLE_EQ(m2.discount_rate, 0.0);
  EXPECT_DOUBLE_EQ(m2.tax_rate, 0.0);

  const auto& m3 = metrics[2];
  EXPECT_EQ(m3.item_id, 3);
  EXPECT_DOUBLE_EQ(m3.final_total, 3200.0);
  EXPECT_EQ(m3.quantity_group, 0);

  const auto& m4 = metrics[3];
  EXPECT_EQ(m4.item_id, 4);
  EXPECT_DOUBLE_EQ(m4.final_total, 82.5);
}
