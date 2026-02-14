#include <gtest/gtest.h>
#include "cascade_delete_demo.hpp"

namespace cascade_delete_demo {

TEST(sqlite, cascade_delete_demo) {
  using namespace sqlgen;
  
  auto conn = sqlite::connect("test_db.sqlite").value();
  
  drop<Child>(conn);
  drop<Parent>(conn);
  create_table<Parent>(conn);
  create_table<Child>(conn);

  auto parent = Parent{.parent_id = 1, .name = "Test Parent"};
  auto children = std::vector<Child>{
      {.child_id = 1, .parent_id = 1, .note = "First Child"},
      {.child_id = 2, .parent_id = 1, .note = "Second Child"},
      {.child_id = 3, .parent_id = 1, .note = "Third Child"}
  };

  insert(conn, parent);
  insert(conn, children);

  auto children_before = sqlgen::read<std::vector<Child>>(conn).value();
  EXPECT_EQ(children_before.size(), 3);

  ASSERT_TRUE(cascade_delete_demo(1));

  auto children_after = sqlgen::read<std::vector<Child>>(conn).value();
  EXPECT_EQ(children_after.size(), 0);
}

}  // namespace cascade_delete_demo
