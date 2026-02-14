#pragma once

#include <ranges>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace query_daily_traffic_metrics {

struct PageVisit {
  sqlgen::PrimaryKey<int> visit_id;
  std::string url;
  sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S"> visit_time;
};

struct DailyTraffic {
  std::string visit_date;
  int total_visits;
  int unique_pages;
};

/**
 * Function: Calculate daily traffic metrics from a log table.
 * 
 * @return List of daily traffic metrics
 */
std::vector<DailyTraffic> query_daily_traffic_metrics() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn_result = sqlite::connect("test_db.sqlite");
  if (!conn_result) return {};
  auto conn = conn_result.value();

  // Create table if not exists (helper)
  create_table<PageVisit>(conn);
  
  std::string view_sql = R"(
    CREATE TABLE IF NOT EXISTS DailyTraffic AS
    SELECT strftime('%Y-%m-%d', visit_time) as visit_date, 
           COUNT(*) as total_visits, 
           COUNT(DISTINCT url) as unique_pages
    FROM PageVisit
    GROUP BY visit_date
    ORDER BY visit_date;
  )";
  
  exec(conn, view_sql);

  auto results = sqlgen::read<std::vector<DailyTraffic>>(conn).value();
  return results;
}

}  // namespace query_daily_traffic_metrics
