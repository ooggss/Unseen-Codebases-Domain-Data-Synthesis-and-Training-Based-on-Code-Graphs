#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace analysis_temporal_data {

struct Event {
  sqlgen::PrimaryKey<int> event_id;
  std::string event_name;
  sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S"> start_time;
  std::optional<sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S">> end_time;
  sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S"> created_at;
};

struct TemporalAnalysis {
  int event_id;
  std::string event_name;
  int start_day;
  int start_month;
  int start_year;
  int start_hour;
  int start_minute;
  int start_second;
  int start_weekday;
  int64_t start_epoch;
  std::optional<double> duration_days;
};

/**
 * @brief Analyze temporal data for a collection of events.
 *
 * Inserts the provided events into a temporary SQLite table, runs a query
 * to extract date/time parts and compute duration, and returns the results
 * as a vector of TemporalAnalysis.
 *
 * @param events Vector of Event records to analyze.
 * @return std::vector<TemporalAnalysis> Analysis results for each event that has an end_time.
 */
std::vector<TemporalAnalysis> analyze_temporal_data () {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  const auto query =
      select_from<Event>(
          cast<int>("event_id"_c).as<"event_id">(), "event_name"_c, day("start_time"_c).as<"start_day">(),
          month("start_time"_c).as<"start_month">(),
          year("start_time"_c).as<"start_year">(),
          hour("start_time"_c).as<"start_hour">(),
          minute("start_time"_c).as<"start_minute">(),
          second("start_time"_c).as<"start_second">(),
          weekday("start_time"_c).as<"start_weekday">(),
          unixepoch("start_time"_c).as<"start_epoch">(),
          floor(days_between("start_time"_c, "end_time"_c)).as<"duration_days">()) |
      where("end_time"_c.is_not_null()) | to<std::vector<TemporalAnalysis>>;

  return sqlite::connect("test_db.sqlite")
      .and_then(query)
      .value();
}

}