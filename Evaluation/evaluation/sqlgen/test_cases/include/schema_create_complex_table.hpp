#pragma once

#include <ranges>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace schema_create_complex_table {

struct UserProfile {
  sqlgen::PrimaryKey<int, sqlgen::auto_incr> user_id;
  sqlgen::Unique<std::string> username;
  sqlgen::Unique<std::string> email;
  int age;
  std::string bio;
  sqlgen::DateTime created_at;
  bool is_verified;
};

/**
 * Function: Create a table with various constraints and data types.
 * @return true if creation succeeds, false otherwise
 */
bool create_complex_table() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn_result = sqlite::connect("test_db.sqlite");
  if (!conn_result) return false;

  auto conn = conn_result.value();
  
  // Create table using sqlgen
  auto create_result = create_table<UserProfile>(conn);
  if (!create_result) return false;
  
  return true;
}

}  // namespace schema_create_complex_table
