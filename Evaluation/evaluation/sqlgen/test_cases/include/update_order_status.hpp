#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <string>
#include <vector>

namespace update_order_status {

struct Order {
  sqlgen::PrimaryKey<int> order_id;
  std::string status;
  sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S"> order_date;
  double total_amount;
};

/**
 * @brief Update the status of orders based on specific criteria.
 * @return true If the update is successful, false otherwise.
 */
bool update_order_status() {
  using namespace sqlgen;
  auto conn = sqlite::connect("test_db.sqlite");
  if (!conn) return 0;
  create_table<Order>(conn);
  auto res = exec(conn, "UPDATE \"Order\" SET status = 'expired' "
                        "WHERE status = 'pending' AND order_date < DATE('2024-01-01');");
  if (!res) return false;
  return true;
}

}  // namespace update_order_status

