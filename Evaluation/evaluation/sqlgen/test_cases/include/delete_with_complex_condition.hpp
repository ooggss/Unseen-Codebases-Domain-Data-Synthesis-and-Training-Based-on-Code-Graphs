#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <string>

namespace delete_with_complex_condition {

struct User {
    sqlgen::PrimaryKey<int> id;
    int age;
    std::string status;
};

/**
 * This function deletes users with age less than 18 or inactive status.
 */
inline void delete_with_complex_condition() {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    auto conn = sqlite::connect("test_db.sqlite");
    auto query = delete_from<User> | where("age"_c < 18 or "status"_c == "inactive");
    query(conn);
    return;
}

}  // namespace delete_with_complex_condition
