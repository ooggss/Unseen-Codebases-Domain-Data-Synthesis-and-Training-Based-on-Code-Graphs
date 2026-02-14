#include <gtest/gtest.h>
#include "replace_text_in_notes.hpp"

namespace replace_text_in_notes {

TEST(sqlite, replace_text_in_notes) {
  using namespace sqlgen;
  auto conn = sqlite::connect("test_db.sqlite").value();
  drop<Note>(conn);
  create_table<Note>(conn);
  insert(conn, std::vector<Note>{{1, "foo ok"}, {2, "no change"}});
  auto rows = replace_text_in_notes();
  ASSERT_EQ(rows.size(), 2);
  ASSERT_EQ(rows[0].updated_content, "bar ok");
  ASSERT_EQ(rows[1].updated_content, "no change");
}

}  // namespace replace_text_in_notes

