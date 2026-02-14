#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace inventory_bulk_write_and_read {

struct Inventory {
  sqlgen::PrimaryKey<int> item_id;
  std::string name;
  int quantity;
  std::string location;
};

/**
 * description: inventory_bulk_write_and_read.
 * This function demonstrates how to perform bulk write and read operations on an inventory table.
 * It first drops and recreates the table, then writes the given items to the table.
 * Finally, it reads back the items with quantity > 50, orders them by quantity in descending order,
 * and returns true if at least one item is found.
 * Returns: bool.
 */
std::vector<Inventory> inventory_bulk_write_and_read(const std::vector<Inventory>& items) {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn = sqlite::connect("test_db.sqlite").value();
  write(conn, items);

  const auto rows =
      (sqlgen::read<std::vector<Inventory>> |
       where("quantity"_c > 50) | order_by("quantity"_c.desc()))(conn)
          .value_or(std::vector<Inventory>{});
  return rows;
}

}  // namespace inventory_bulk_write_and_read

