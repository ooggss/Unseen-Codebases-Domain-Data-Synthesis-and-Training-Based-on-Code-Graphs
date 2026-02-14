#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <string>

namespace order_by_descending {

struct Score {
    sqlgen::PrimaryKey<int> id;
    int points;
};

/**
 * This function demonstrates ORDER BY DESC.
 * Returns: std::vector<Score>.
 */
std::vector<Score> order_by_descending() {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    auto query = sqlgen::read<std::vector<Score>> | sqlgen::order_by("points"_c.desc());
    auto conn = sqlite::connect("test_db.sqlite").value();
    return query(conn).value_or(std::vector<Score>{});
}

}  // namespace order_by_descending
