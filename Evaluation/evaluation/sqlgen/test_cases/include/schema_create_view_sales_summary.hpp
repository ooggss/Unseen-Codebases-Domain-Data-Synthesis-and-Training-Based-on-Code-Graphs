#pragma once

#include <ranges>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace schema_create_view_sales_summary {

struct Product {
  sqlgen::PrimaryKey<int> product_id;
  std::string name;
  double price;
  int stock;
};

struct Sale {
  sqlgen::PrimaryKey<int, sqlgen::auto_incr> sale_id;
  int product_id;
  int quantity;
  double amount;
};

struct SalesSummary {
  static constexpr bool is_view = true;
  std::string product_name;
  int total_quantity;
  double total_revenue;
};

/**
 * Function: Create a view SalesSummary that aggregates sales by product.
 * @return A vector of SalesSummary structs
 */
std::vector<SalesSummary> create_view_sales_summary() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn_result = sqlite::connect("test_db.sqlite");
  if (!conn_result) return {};
  auto conn = conn_result.value();

  create_table<Product>(conn);
  create_table<Sale>(conn);

  const auto summary_query =
      select_from<Product, "t2">("name"_t2 | as<"product_name">,
                                 sum("quantity"_t1).as<"total_quantity">(),
                                 sum("amount"_t1).as<"total_revenue">()) |
      inner_join<Sale, "t1">("product_id"_t2 == "product_id"_t1) |
      group_by("name"_t2);
  const auto create_view = create_as<SalesSummary>(summary_query) | if_not_exists;
  auto res = create_view(conn);
  
  auto read_view = sqlgen::read<std::vector<SalesSummary>>(conn);
  return read_view.value_or({});
}

}  // namespace schema_create_view_sales_summary
