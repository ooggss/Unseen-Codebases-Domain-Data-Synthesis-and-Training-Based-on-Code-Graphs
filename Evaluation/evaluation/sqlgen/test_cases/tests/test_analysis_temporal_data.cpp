#include <gtest/gtest.h>
#include <sqlgen/sqlite.hpp>
#include "analysis_temporal_data.hpp"

namespace analysis_temporal_data {

TEST(sqlite, AnalyzeTemporalData) {
  using namespace sqlgen;
  using namespace sqlgen::literals;
  using Timestamp = sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S">;
  
  std::vector<Event> events = {
      {1, "New Year Party", Timestamp("2023-01-01 20:00:00"), 
       Timestamp("2023-01-02 02:00:00"), Timestamp("2022-12-01 10:00:00")},
      {2, "Conference", Timestamp("2023-03-15 09:00:00"), 
       Timestamp("2023-03-17 17:00:00"), Timestamp("2023-01-15 10:00:00")},
      {3, "Meeting", Timestamp("2023-06-01 14:30:45"), 
       std::nullopt, Timestamp("2023-05-20 10:00:00")}
  };
  auto conn = sqlite::connect("test_db.sqlite").value();
  drop<Event>(conn);
  create_table<Event>(conn);
  insert(conn, events);

  auto results = analyze_temporal_data();

  // Should only return 2 events because Meeting has null end_time
  ASSERT_EQ(results.size(), 2);

  // Verify New Year Party
  const auto& party = results[0];
  EXPECT_EQ(party.event_id, 1);
  EXPECT_EQ(party.event_name, "New Year Party");
  EXPECT_EQ(party.start_day, 1);
  EXPECT_EQ(party.start_month, 1);
  EXPECT_EQ(party.start_year, 2023);
  EXPECT_EQ(party.start_hour, 20);
  EXPECT_EQ(party.start_minute, 0);
  EXPECT_EQ(party.start_second, 0);
  // 2023-01-01 was a Sunday (0)
  EXPECT_EQ(party.start_weekday, 0); 
  // Unix epoch for 2023-01-01 20:00:00 UTC
  EXPECT_GT(party.start_epoch, 0);
  
  // Duration: 20:00 to 02:00 next day is < 1 day, so 0 days
  EXPECT_EQ(party.duration_days, 0);

  // Verify Conference
  const auto& conference = results[1];
  EXPECT_EQ(conference.event_id, 2);
  EXPECT_EQ(conference.event_name, "Conference");
  EXPECT_EQ(conference.start_day, 15);
  EXPECT_EQ(conference.start_month, 3);
  EXPECT_EQ(conference.start_year, 2023);
  // 2023-03-15 was a Wednesday (3)
  EXPECT_EQ(conference.start_weekday, 3);
  
  // Duration: March 15 to March 17 is 2 days
  EXPECT_EQ(conference.duration_days, 2);
}

}