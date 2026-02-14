#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <sqlgen/transpilation/read_to_select_from.hpp>
#include <string>

namespace read_to_select_from_usage {

struct User {
  sqlgen::PrimaryKey<int> id;
  std::string name;
  int age;
};

/**
 * Constructs a query selecting all columns from `User` where age is greater than 18 with a limit of 10.
 * Returns: std::vector<User>.
 */
inline std::vector<User> read_to_select_from_usage() {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    auto select_query = sqlgen::read<std::vector<User>> | where("age"_c > 18) | limit(10);
    auto conn = sqlite::connect("test_db.sqlite").value();
    return select_query(conn).value();
}

}  // namespace read_to_select_from_usage
