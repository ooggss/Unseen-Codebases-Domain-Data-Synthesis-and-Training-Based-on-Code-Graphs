#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <string>

namespace concat_function {

struct Person {
  sqlgen::PrimaryKey<int> id;
  std::string first_name;
  std::string last_name;
};

struct FullName {
  std::string full_name;
};

/**
 * This function queries the full names of all persons in the `Person` table.
 * Returns: std::vector<FullName>.
 */
inline std::vector<FullName> concat_function() {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    auto query = select_from<Person>(
        concat("first_name"_c, " ", "last_name"_c) | as<"full_name">
        ) | to<std::vector<FullName>>;
    return query(sqlite::connect("test_db.sqlite").value()).value();
}

}  // namespace concat_function
