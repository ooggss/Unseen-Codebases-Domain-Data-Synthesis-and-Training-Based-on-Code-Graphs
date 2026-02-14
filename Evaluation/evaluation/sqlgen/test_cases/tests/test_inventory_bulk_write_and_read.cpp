#include <gtest/gtest.h>
#include "inventory_bulk_write_and_read.hpp"

namespace inventory_bulk_write_and_read {

TEST(sqlite, inventory_bulk_write_and_read) {
  using namespace sqlgen;
  using namespace sqlgen::literals;
  auto conn = sqlite::connect("test_db.sqlite").value();
  drop<Inventory>(conn);
  create_table<Inventory>(conn);
  std::vector<Inventory> items{{1, "A", 40, "W1"},
                               {2, "B", 60, "W2"},
                               {3, "C", 80, "W2"}};
  std::vector<Inventory> rows = inventory_bulk_write_and_read(items);
  ASSERT_EQ(rows.size(), 2);
  ASSERT_EQ(rows[0].quantity, 80);
  ASSERT_EQ(rows[1].quantity, 60);
}

}  // namespace inventory_bulk_write_and_read

