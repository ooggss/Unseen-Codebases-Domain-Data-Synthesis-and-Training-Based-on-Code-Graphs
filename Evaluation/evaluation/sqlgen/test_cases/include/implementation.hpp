#pragma once

#include <filesystem>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <string>

#include "eas_common.hpp"

namespace update_eas_table {

void update_eas_table() {
  design_eas_database_with_major();

  const std::string db_path = "data/eas_database.db";
  if (!std::filesystem::exists(db_path)) {
    throw std::runtime_error("Database file does not exist: " + db_path);
  }

  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn = sqlite::connect(db_path);
  if (!conn) {
    throw std::runtime_error("Failed to connect to database");
  }

  exec(conn, "ALTER TABLE Score ADD COLUMN Grade CHAR(1) NOT NULL DEFAULT 'A';").value();

  exec(conn, "ALTER TABLE Student ADD COLUMN Age INTEGER;").value();

  conn.and_then(sqlgen::drop<Major>).value();
}

} // namespace update_eas_table
