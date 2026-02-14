#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace limit_recent_events {

struct Event {
  sqlgen::PrimaryKey<int> event_id;
  std::string name;
  sqlgen::Timestamp<"%Y-%m-%d %H:%M:%S"> created_at;
};

/**
 * description: limit_recent_events.
 * This function demonstrates how to limit the number of recent events returned.
 * It orders the events by created_at in descending order and returns the top n events.
 * Returns: std::vector<Event>.
 */
std::vector<Event> limit_recent_events(size_t n = 10) {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn_res = sqlite::connect("test_db.sqlite");
  if (!conn_res) return {};
  auto conn = conn_res.value();

  create_table<Event>(conn);

  const auto query =
      select_from<Event>(col<"event_id"> | as<"event_id">, col<"name"> | as<"name">,
                         col<"created_at"> | as<"created_at">) |
      order_by(col<"created_at">.desc()) | limit(n) | to<std::vector<Event>>;
  return query(conn).value();
}

}  // namespace limit_recent_events

