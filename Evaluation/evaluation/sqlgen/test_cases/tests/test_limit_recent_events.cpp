#include <gtest/gtest.h>
#include "limit_recent_events.hpp"

namespace limit_recent_events {

TEST(sqlite, limit_recent_events) {
  using namespace sqlgen;
  auto conn = sqlite::connect("test_db.sqlite").value();
  drop<Event>(conn);
  create_table<Event>(conn);
  insert(conn, std::vector<Event>{
      {1, "A", sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S">{"2024-01-01 08:00:00"}},
      {2, "B", sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S">{"2024-01-01 09:00:00"}},
      {3, "C", sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S">{"2024-01-01 10:00:00"}}});
  auto rows = limit_recent_events(2);
  ASSERT_EQ(rows.size(), 2);
  ASSERT_EQ(rows[0].name, "C");
  ASSERT_EQ(rows[1].name, "B");
}

}  // namespace limit_recent_events

