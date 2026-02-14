#include <gtest/gtest.h>
#include "update_order_status.hpp"

namespace update_order_status {

TEST(sqlite, update_order_status) {
  using namespace sqlgen;
  auto conn = sqlite::connect("test_db.sqlite").value();
  drop<Order>(conn);
  create_table<Order>(conn);

  std::vector<Order> orders = {
      {1, "pending", "2023-01-01 00:00:00", 100.0},
      {2, "pending", "2030-01-01 00:00:00", 150.0},
      {3, "shipped", "2024-12-01 00:00:00", 200.0}};
  insert(conn, orders);

  ASSERT_TRUE(update_order_status());
  auto rows = sqlgen::read<std::vector<Order>>(conn).value();
  auto find = [&](int id) {
    return std::find_if(rows.begin(), rows.end(),
                        [&](const Order& o) { return o.order_id.value() == id; });
  };
  EXPECT_EQ(find(1)->status, "expired");
  EXPECT_EQ(find(2)->status, "pending");
  EXPECT_EQ(find(3)->status, "shipped");
}

}  // namespace update_order_status

