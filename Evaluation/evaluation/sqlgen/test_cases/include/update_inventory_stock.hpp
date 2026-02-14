#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <unordered_map>

namespace update_inventory_stock {

struct Product {
  sqlgen::PrimaryKey<int> product_id;
  int stock;
};

/**
 * @brief Update inventory stock based on a shipment.
 * @param received A map of {product_id, quantity_received}.
 * @return true If all updates are successful, false otherwise.
 */
bool update_inventory_stock(const std::unordered_map<int, int>& received) {
  using namespace sqlgen;
  using namespace sqlgen::literals;
  auto conn_res = sqlite::connect("test_db.sqlite");
  if (!conn_res) return false;
  create_table<Product>(conn_res);

  auto txn_res = begin_transaction(conn_res.value());
  if (!txn_res) return false;
  auto txn = txn_res.value();
  
  for (const auto& [pid, qty] : received) {
    std::string sql = "UPDATE Product SET stock = stock + " + std::to_string(qty) +
                      " WHERE product_id = " + std::to_string(pid) + ";";
    auto exec_res = exec(txn, sql);
    if (!exec_res) {
      return false;
    }
  }
  
  auto commit_res = commit(txn);
  return commit_res.has_value();
}

}  // namespace update_inventory_stock
