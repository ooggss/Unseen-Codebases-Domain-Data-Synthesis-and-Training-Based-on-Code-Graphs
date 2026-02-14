#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <string>
#include <vector>

namespace in_operator_usage {

struct Status {
  sqlgen::PrimaryKey<int> id;
  int code;
};

/**
 * This function query records in the `Status` table where `code` is in (1, 2, 3).
 * Returns: vector<Status>
 */
inline std::vector<Status> in_operator_usage() {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    auto query = sqlgen::read<std::vector<Status>> | sqlgen::where("code"_c.in(1, 2, 3));
    auto conn = sqlite::connect("test_db.sqlite").value();
    return query(conn).value_or(std::vector<Status>{});
}

}  // namespace in_operator_usage
