#include <gtest/gtest.h>
#include "soft_delete_records.hpp"

namespace soft_delete_records {

TEST(sqlite, soft_delete_records) {
  using namespace sqlgen;
  auto conn = sqlite::connect("test_db.sqlite").value();
  drop<Document>(conn);
  create_table<Document>(conn);

  std::vector<Document> docs = {
      {1, "doc1", 0},
      {2, "doc2", 0},
      {3, "doc3", 0}};
  insert(conn, docs);

  ASSERT_TRUE(soft_delete_records({1, 3}));
  auto rows = sqlgen::read<std::vector<Document>>(conn).value();

  auto find = [&](int id) {
    return std::find_if(rows.begin(), rows.end(),
                        [&](const Document& d) { return d.doc_id.value() == id; });
  };

  EXPECT_EQ(find(1)->is_deleted, 1);
  EXPECT_EQ(find(3)->is_deleted, 1);
  EXPECT_EQ(find(2)->is_deleted, 0);
}

}  // namespace soft_delete_records

