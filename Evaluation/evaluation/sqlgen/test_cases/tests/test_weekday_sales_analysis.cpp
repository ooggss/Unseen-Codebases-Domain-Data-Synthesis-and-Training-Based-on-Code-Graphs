#include <gtest/gtest.h>
#include "weekday_sales_analysis.hpp"

namespace weekday_sales_analysis {

TEST(sqlite, weekday_sales_analysis) {
  using namespace sqlgen;
  auto conn = sqlite::connect("test_db.sqlite").value();
  drop<Sales>(conn);
  create_table<Sales>(conn);
  insert(conn, std::vector<Sales>{
      {1, 10, 2, "2024-01-01"},
      {2, 11, 3, "2024-01-02"},
      {3, 12, 1, "2024-01-03"},
      {4, 13, 2, "2024-01-01"},
      {5, 14, 3, "2024-01-02"},
      {6, 15, 2, "2024-01-03"},
    });
  auto rows = weekday_sales_analysis();
  ASSERT_EQ(rows.size(), 3);
  ASSERT_EQ(rows[0].total_quantity, 4);
  ASSERT_EQ(rows[1].total_quantity, 6);
  ASSERT_EQ(rows[2].total_quantity, 3);
}

}  // namespace weekday_sales_analysis

