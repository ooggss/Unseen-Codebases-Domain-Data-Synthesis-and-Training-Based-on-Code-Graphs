#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <string>

namespace like_pattern_matching {

struct Product {
  sqlgen::PrimaryKey<int> id;
  std::string name;
};

/**
 * This function demonstrates LIKE usage.
 * Returns: std::vector<Product>.
 */
inline std::vector<Product> like_pattern_matching() {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    auto query = sqlgen::read<std::vector<Product>> | sqlgen::where("name"_c.like("A%"));
    auto conn = sqlite::connect("test_db.sqlite").value();
    return query(conn).value();
}

}  // namespace like_pattern_matching
