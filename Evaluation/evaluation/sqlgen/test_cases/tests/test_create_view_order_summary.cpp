#include <gtest/gtest.h>
#include "create_view_order_summary.hpp"

namespace create_view_order_summary {

TEST(sqlite, create_view_order_summary) {
  using namespace sqlgen;
  using namespace sqlgen::literals;
  auto conn = sqlite::connect("test_db.sqlite").value();
  drop<Order>(conn);
  drop<OrderItem>(conn);
  create_table<Order>(conn);
  create_table<OrderItem>(conn);

  insert(conn, std::vector<Order>{{1, "Alice"}, {2, "Bob"}});
  insert(conn, std::vector<OrderItem>{{1, 1, 10.0, 2}, {2, 1, 5.0, 1}, {3, 2, 7.0, 3}});

  std::vector<OrderSummary> rows = create_view_order_summary();
  ASSERT_GE(rows.size(), 2);
  ASSERT_EQ(rows[0].customer, "Alice");
  ASSERT_EQ(rows[0].total, 25.0);
  ASSERT_EQ(rows[1].customer, "Bob");
  ASSERT_EQ(rows[1].total, 21.0);
}

}  // namespace create_view_order_summary

