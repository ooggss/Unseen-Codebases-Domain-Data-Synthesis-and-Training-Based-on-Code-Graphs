#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <string>

namespace create_table_as_select {

struct Source {
  sqlgen::PrimaryKey<int> id;
  int value;
};

struct Target {
  int value;
};

/**
 * Description: This function creates a table `Target` from a select query on `Source` 
 * Returns: std::vector<Target>.
 */
inline std::vector<Target> create_table_as_select() {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    auto select_query = select_from<Source>("value"_c) | where("value"_c > 100);
    auto create_table_query = create_as<Target>(select_query);
    auto conn = sqlite::connect("test_db.sqlite").value();
    create_table_query(conn).value();
    auto select_target_query = select_from<Target>("value"_c) | to<std::vector<Target>>;
    return select_target_query(conn).value();
}

}  // namespace create_table_as_select
