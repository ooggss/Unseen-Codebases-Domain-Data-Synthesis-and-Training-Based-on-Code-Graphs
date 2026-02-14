#pragma once

#include <ranges>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace query_customer_purchase_history {

struct Customer {
  sqlgen::PrimaryKey<int> customer_id;
  std::string name;
  std::string email;
};

struct Product {
  sqlgen::PrimaryKey<int> product_id;
  std::string name;
  double price;
};

struct Order {
  sqlgen::PrimaryKey<int> order_id;
  sqlgen::ForeignKey<int, Customer, "customer_id"> customer_id;
  sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S"> order_date;
  double total_amount;
};

struct OrderItem {
  sqlgen::PrimaryKey<int> item_id;
  sqlgen::ForeignKey<int, Order, "order_id"> order_id;
  sqlgen::ForeignKey<int, Product, "product_id"> product_id;
  int quantity;
};

struct PurchaseHistory {
  std::string product_name;
  sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S"> order_date;
  int quantity;
};

/**
 * Function: Retrieve a customer's purchase history with product details.
 * 
 * @param customer_id ID of the customer to query
 * @return List of purchase history items
 */
std::vector<PurchaseHistory> query_customer_purchase_history(int customer_id) {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn_result = sqlite::connect("test_db.sqlite");
  if (!conn_result) return {};
  auto conn = conn_result.value();

  // Create tables if not exists (helper)
  create_table<Customer>(conn);
  create_table<Product>(conn);
  create_table<Order>(conn);
  create_table<OrderItem>(conn);

  // Drop view if exists to ensure we create it with the current customer_id
  (drop<PurchaseHistory> | if_exists)(conn);

  const auto query = 
      select_from<Customer, "t1">(
          "name"_t4 | as<"product_name">,
          "order_date"_t2 | as<"order_date">,
          "quantity"_t3 | as<"quantity">) |
      inner_join<Order, "t2">("customer_id"_t1 == "customer_id"_t2) |
      inner_join<OrderItem, "t3">("order_id"_t2 == "order_id"_t3) |
      inner_join<Product, "t4">("product_id"_t3 == "product_id"_t4) |
      where("customer_id"_t1 == customer_id) |
      order_by("order_date"_t2.desc());

  const auto create_view = create_as<PurchaseHistory>(query);
  create_view(conn);

  auto rows = sqlgen::read<std::vector<PurchaseHistory>>(conn).value();
  return rows;
}

}  // namespace query_customer_purchase_history
