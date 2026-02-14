#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace create_view_order_summary {

struct Order {
  sqlgen::PrimaryKey<int> order_id;
  std::string customer;
};

struct OrderItem {
  sqlgen::PrimaryKey<int> item_id;
  int order_id;
  double unit_price;
  int quantity;
};

struct OrderSummary {
  static constexpr const char* tablename = "OrderSummaryView";
  static constexpr bool is_view = true;
  sqlgen::PrimaryKey<int> order_id;
  std::string customer;
  double total;
};

/**
 * Description: Create a view `OrderSummaryView` that shows order ID, customer name, and (unit_price * quantity) as total price for each order.
 * Returns: std::vector<OrderSummary>.
 */
std::vector<OrderSummary> create_view_order_summary() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn = sqlite::connect("test_db.sqlite").value();

  const auto query =
      select_from<Order, "o">(col<"order_id", "o"> | as<"order_id">,
                              col<"customer", "o"> | as<"customer">,
                              sum(col<"unit_price", "oi"> * col<"quantity", "oi">) |
                                  as<"total">) |
      inner_join<OrderItem, "oi">(col<"order_id", "o"> == col<"order_id", "oi">) |
      group_by(col<"order_id", "o">, col<"customer", "o">) | to<std::vector<OrderSummary>>;

  create_or_replace_view_as<OrderSummary>(query)(conn);

  const auto read_view =
      sqlgen::read<std::vector<OrderSummary>>(conn).value_or(
          std::vector<OrderSummary>{});
  return read_view;
}

}  // namespace create_view_order_summary

