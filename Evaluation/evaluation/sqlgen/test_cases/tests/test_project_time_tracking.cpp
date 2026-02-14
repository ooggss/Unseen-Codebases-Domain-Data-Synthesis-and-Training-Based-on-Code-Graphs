#include <gtest/gtest.h>
#include "project_time_tracking.hpp"

namespace project_time_tracking {

TEST(sqlite, project_time_tracking) {
  using namespace sqlgen;
  auto conn = sqlite::connect("test_db.sqlite").value();
  drop<Project>(conn);
  drop<TimeLog>(conn);
  create_table<Project>(conn);
  create_table<TimeLog>(conn);

  insert(conn, std::vector<Project>{{1, "P1"}});
  insert(conn, std::vector<TimeLog>{
      {1, 1, sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S">{"2024-01-01 10:00:00"},
       sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S">{"2024-01-03 10:00:00"}}});

  auto rows = project_time_tracking();
  ASSERT_EQ(rows.size(), 1);
  ASSERT_EQ(rows[0].project_id.value(), 1);
  ASSERT_EQ(rows[0].name, "P1");
  ASSERT_EQ(rows[0].day, 1);
  ASSERT_EQ(rows[0].month, 1);
  ASSERT_EQ(rows[0].year, 2024);
  ASSERT_EQ(rows[0].hour, 10);
  ASSERT_EQ(rows[0].minute, 0);
  ASSERT_EQ(rows[0].second, 0);
  ASSERT_EQ(rows[0].duration_days, 2);
}

}  // namespace project_time_tracking

