#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <string>

namespace aggregation_arithmetic {

struct Product {
  sqlgen::PrimaryKey<int> id;
  double price;
};

/**
 * This function demonstrates arithmetic on aggregations.
 * Returns: double.
 */
inline double aggregation_arithmetic() {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    auto conn = sqlite::connect("test_db.sqlite").value();
    auto avg_query = sqlgen::select_from<Product>(avg("price"_c) | as<"avg_price">) |
                 to<double>;
    auto result = avg_query(conn).value();
    return result + 10.0;
}

}  // namespace aggregation_arithmetic
