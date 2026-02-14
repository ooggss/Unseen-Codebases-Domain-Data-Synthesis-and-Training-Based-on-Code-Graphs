#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace weekday_sales_analysis {

struct Sales {
  sqlgen::PrimaryKey<int> sale_id;
  int product_id;
  int quantity;
  sqlgen::Date sale_date;
};

struct WeekdayStats {
  int weekday;
  int total_quantity;
};

/**
 * Description: This function analyzes sales data to calculate total quantity sold for each weekday.
 * Returns: std::vector<WeekdayStats>.
 */
std::vector<WeekdayStats> weekday_sales_analysis() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn = sqlite::connect("test_db.sqlite").value();

  const auto query =
      select_from<Sales>(weekday(col<"sale_date">) | as<"weekday">,
                         sum(col<"quantity">) | as<"total_quantity">) |
      group_by(col<"sale_date">) | to<std::vector<WeekdayStats>>;

  return query(conn).value();
}

}  // namespace weekday_sales_analysis

