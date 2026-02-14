#pragma once

#include <filesystem>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>

namespace test_create_eas_database {

  void create_eas_database() {
    const std::string db_path = "test_db.sqlite";
    
    std::filesystem::create_directories("data");
    
    const auto conn = sqlgen::sqlite::connect(db_path);
    
    if (!conn) {
      throw std::runtime_error("Failed to create EAS_DB database");
    }
    
    sqlgen::exec(conn, "ATTACH DATABASE 'test_db.sqlite' AS EAS_DB;").value();
  }

}
