#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <string>

namespace update_with_arithmetic {

struct Player {
  sqlgen::PrimaryKey<int> id;
  int score;
};

/**
 * This function demonstrates updating a column with arithmetic.
 * Returns: std::vector<Player>.
 */
inline std::vector<Player> update_with_arithmetic() {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    auto conn = sqlite::connect("test_db.sqlite").value();

    std::string sql = "UPDATE Player SET score = score + 10;";
    exec(conn, sql);
    auto read_query = sqlgen::read<std::vector<Player>>;
    return read_query(conn).value();
}

}  // namespace update_with_arithmetic
