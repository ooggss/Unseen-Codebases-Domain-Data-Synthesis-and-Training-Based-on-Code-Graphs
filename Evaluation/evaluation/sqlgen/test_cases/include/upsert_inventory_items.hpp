#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace upsert_inventory_items {

struct Inventory {
  sqlgen::PrimaryKey<int> item_id;
  std::string name;
  int quantity;
};

/**
 * This function demonstrates how to use upsert (insert or replace) statements in sqlgen write API.
 * It inserts or replaces the given inventory items in the Inventory table.
 * Returns: true if the item is inserted, false if the item is already in the table.
 */
bool upsert_inventory_items(Inventory item) {
  using namespace sqlgen;
  using namespace sqlgen::literals;
  auto conn = sqlite::connect("test_db.sqlite").value();
  int old_size = sqlgen::read<std::vector<Inventory>>(conn).value_or(std::vector<Inventory>{}).size();
  insert_or_replace(std::vector<Inventory>{item})(conn);
  const auto rows =
      sqlgen::read<std::vector<Inventory>>(conn).value_or(std::vector<Inventory>{});
  return rows.size() > old_size;
}

}  // namespace upsert_inventory_items

