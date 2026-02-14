#include <gtest/gtest.h>
#include "upsert_inventory_items.hpp"

namespace upsert_inventory_items {

TEST(sqlite, upsert_inventory_items) {
  using namespace sqlgen;
  using namespace sqlgen::literals;
  auto conn = sqlite::connect("test_db.sqlite").value();
  drop<Inventory>(conn);
  create_table<Inventory>(conn);
  Inventory item1 = {1, "A", 10};
  ASSERT_TRUE(upsert_inventory_items(item1));
  Inventory item2_old = {2, "B", 20};
  Inventory item2_new = {2, "B2", 30};
  ASSERT_TRUE(upsert_inventory_items(item2_old));
  ASSERT_FALSE(upsert_inventory_items(item2_new));
  auto query = sqlgen::read<std::vector<Inventory>> | where("item_id"_c == 2);
  auto rows = query(conn).value();
  ASSERT_EQ(rows[0].name, "B2");

  // insert(conn, std::vector<Inventory>{{1, "A", 10}, {2, "B", 20}});
  // ASSERT_TRUE(upsert_inventory_items(std::vector<Inventory>{{2, "B2", 30}, {3, "C", 5}}));
}

}  // namespace upsert_inventory_items

