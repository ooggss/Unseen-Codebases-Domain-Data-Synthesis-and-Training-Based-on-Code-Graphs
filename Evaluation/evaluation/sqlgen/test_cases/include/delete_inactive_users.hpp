#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <string>
#include <vector>

namespace delete_inactive_users {

struct User {
  sqlgen::PrimaryKey<int> user_id;
  std::string username;
  sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S"> last_login;
  std::string status;
};

/**
 * This function deletes inactive users from the "User" table in the "test_db.sqlite" database.
 * Inactive users are defined as those who have not logged in since 2025-01-01.
 * Returns: bool.
 */
bool delete_inactive_users() {
  using namespace sqlgen;
  using namespace sqlgen::literals;
  auto conn_res = sqlite::connect("test_db.sqlite");
  if (!conn_res) return false;
  
  auto txn_res = begin_transaction(conn_res.value());
  if (!txn_res) return false;
  auto txn = txn_res.value();
  
  std::string sql = "DELETE FROM User WHERE last_login < DATE('2025-01-01');";
  auto exec_res = exec(txn, sql);
  if (!exec_res) {
    return false;
  }
  
  auto commit_res = commit(txn);
  return commit_res.has_value();
}

}  // namespace delete_inactive_users

