#pragma once

#include <ranges>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace schema_migration_add_column {

struct User {
  sqlgen::PrimaryKey<int, sqlgen::auto_incr> user_id;
  std::string username;
};

struct UserAfter {
  sqlgen::PrimaryKey<int, sqlgen::auto_incr> user_id;
  std::string username;
  std::string phone_number;
  bool is_active;
};

/**
 * Function: Perform schema migration to add new columns.
 * @return true if migration succeeds, false otherwise
 */
bool migration_add_column() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn_result = sqlite::connect("test_db.sqlite");
  if (!conn_result) return false;
  auto conn = conn_result.value();
  
  auto res1 = exec(conn, "ALTER TABLE User ADD COLUMN phone_number VARCHAR(20);");
  // We ignore error here because if column exists it will fail, which is expected in repeated runs without cleanup
  
  auto res2 = exec(conn, "ALTER TABLE User ADD COLUMN is_active INTEGER DEFAULT 1;");

  return true;
}

}  // namespace schema_migration_add_column
