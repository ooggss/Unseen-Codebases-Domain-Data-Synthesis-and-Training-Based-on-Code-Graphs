#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>
#include <optional>

namespace calculate_order_metrics {

struct OrderItem {
  sqlgen::PrimaryKey<int> item_id;
  int order_id;
  int product_id;
  double unit_price;
  int quantity;
  std::optional<double> discount_rate;
  std::optional<double> tax_rate;
};

struct OrderMetrics {
  int item_id;
  int order_id;
  int product_id;
  double unit_price;
  int quantity;
  double discount_rate;
  double tax_rate;
  double gross_total;
  double discounted_total;
  double final_total;
  double unit_cost;
  int quantity_group;
  double estimated_profit;
};

/**
 * Calculate per-item order metrics by querying the OrderItem table
 * and evaluating SQL expressions for totals, discounts, taxes, cost, grouping, and estimated profit.
 * @param items Vector of OrderItem records to analyze.
 * @return std::vector<OrderMetrics> Analysis results for each order item.
 */
std::vector<OrderMetrics> calculate_order_metrics_impl() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn = sqlite::connect("test_db.sqlite").value();

  const auto query = select_from<OrderItem>(
          cast<int>("item_id"_c).as<"item_id">(),
          "order_id"_c,
          "product_id"_c,
          "unit_price"_c,
          "quantity"_c,
          coalesce("discount_rate"_c, 0.0).as<"discount_rate">(),
          coalesce("tax_rate"_c, 0.0).as<"tax_rate">(),
          ("unit_price"_c * "quantity"_c).as<"gross_total">(),
          ("unit_price"_c * "quantity"_c * (coalesce("discount_rate"_c, 0.0) / 100.0 * -1.0 + 1.0)).as<"discounted_total">(),
          ("unit_price"_c * "quantity"_c * (coalesce("discount_rate"_c, 0.0) / 100.0 * -1.0 + 1.0) * (coalesce("tax_rate"_c, 0.0) / 100.0 + 1.0)).as<"final_total">(),
          ("unit_price"_c * "quantity"_c / "quantity"_c).as<"unit_cost">(),
          ("quantity"_c % 10).as<"quantity_group">(),
          ("unit_price"_c * 0.3).as<"estimated_profit">()) |
      to<std::vector<OrderMetrics>>;

  return query(conn).value();
}

}  // namespace calculate_order_metrics
