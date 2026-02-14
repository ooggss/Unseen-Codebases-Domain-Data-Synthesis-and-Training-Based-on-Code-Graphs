#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <optional>
#include <string>
#include <vector>

namespace soft_delete_records {

struct Document {
  sqlgen::PrimaryKey<int> doc_id;
  std::string title;
  int is_deleted;
};

bool soft_delete_records(const std::vector<int>& ids) {
  using namespace sqlgen;
  using namespace sqlgen::literals;
  auto conn_res = sqlite::connect("test_db.sqlite");
  if (!conn_res) return false;
  create_table<Document>(conn_res);

  auto txn_res = begin_transaction(conn_res.value());
  if (!txn_res) return false;
  auto txn = txn_res.value();
  
  for (int id : ids) {
    auto res = (update<Document>("is_deleted"_c.set(1)) |
                where("doc_id"_c == id))(txn->conn());
    if (!res) { (void)txn->rollback(); return false; }
  }
  
  auto commit_res = commit(txn);
  return commit_res.has_value();
}

}  // namespace soft_delete_records
