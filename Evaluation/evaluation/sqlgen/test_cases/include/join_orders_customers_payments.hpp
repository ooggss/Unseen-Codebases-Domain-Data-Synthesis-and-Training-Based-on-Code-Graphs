#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace join_orders_customers_payments {

struct Customer {
  sqlgen::PrimaryKey<int> customer_id;
  std::string name;
};

struct Order {
  sqlgen::PrimaryKey<int> order_id;
  int customer_id;
  sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S"> order_date;
};

struct Payment {
  sqlgen::PrimaryKey<int> payment_id;
  int order_id;
  double amount;
};

struct Consolidated {
  sqlgen::PrimaryKey<int> order_id;
  std::string customer_name;
  double amount;
};

/**
 * This function demonstrates how to join three tables (Orders, Customers, and Payments)
 * and return a consolidated view with order_id, customer_name, and amount.
 * It orders the results by amount in descending order.
 * Returns: std::vector<Consolidated>.
 */
std::vector<Consolidated> join_orders_customers_payments() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn_res = sqlite::connect("test_db.sqlite");
  if (!conn_res) return {};
  auto conn = conn_res.value();

  create_table<Customer>(conn);
  create_table<Order>(conn);
  create_table<Payment>(conn);

  const auto query =
      select_from<Order, "o">(col<"order_id", "o"> | as<"order_id">,
                              col<"name", "c"> | as<"customer_name">,
                              col<"amount", "p"> | as<"amount">) |
      inner_join<Customer, "c">(col<"customer_id", "o"> == col<"customer_id", "c">) |
      inner_join<Payment, "p">(col<"order_id", "o"> == col<"order_id", "p">) |
      order_by(col<"amount", "p">.desc()) | to<std::vector<Consolidated>>;

  return query(conn).value();
}

}  // namespace join_orders_customers_payments

