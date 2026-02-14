#pragma once

#include <filesystem>
#include <map>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <string>
#include <vector>

#include "eas_common.hpp"
using namespace sqlgen;
using namespace sqlgen::literals;

template<typename T>
void add_eas_records(const std::string& table_name,
                     const std::vector<T>& records) {
  
  const std::string db_path = "test_db.sqlite";
  if (!std::filesystem::exists(db_path)) {
    throw std::runtime_error("Database file does not exist: " + db_path);
  }

  auto conn = sqlite::connect(db_path);
  if (!conn) {
    throw std::runtime_error("Failed to connect to database");
  }

  conn.and_then(sqlgen::insert(records));
}

void delete_eas_records_by_id(const std::string& table_name,
                               const std::string& record_id) {
  const std::string db_path = "test_db.sqlite";
  if (!std::filesystem::exists(db_path)) {
    throw std::runtime_error("Database file does not exist: " + db_path);
  }

  auto conn = sqlite::connect(db_path);
  if (!conn) {
    throw std::runtime_error("Failed to connect to database");
  }

  if (table_name == "Student") {
    const auto query = delete_from<Student> | where("SNo"_c == record_id);
    const auto result = query(conn);
  } else if (table_name == "Course") {
    const uint32_t id = static_cast<uint32_t>(std::stoul(record_id));
    const auto query = delete_from<Course> | where("CID"_c == id);
    const auto result = query(conn);
  } else if (table_name == "Score") {
    const uint32_t id = static_cast<uint32_t>(std::stoul(record_id));
    const auto query = delete_from<Score> | where("ScID"_c == id);
    const auto result = query(conn);
  } else {
    throw std::runtime_error("Unknown table: " + table_name);
  }
}
