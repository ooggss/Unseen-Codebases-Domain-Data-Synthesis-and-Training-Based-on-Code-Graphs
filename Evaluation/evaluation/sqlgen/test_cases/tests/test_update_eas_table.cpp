#include <gtest/gtest.h>

#include <filesystem>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>

#include "eas_common.hpp"
#include "update_eas_table.hpp"
using namespace sqlgen;
using namespace sqlgen::literals;

namespace update_eas_table {

TEST(sqlite, test_update_eas_table) {
  const std::string db_path = "test_db.sqlite";
  
  if (std::filesystem::exists(db_path)) {
    std::filesystem::remove(db_path);
  }
  
  design_eas_database_with_major();
  ASSERT_TRUE(std::filesystem::exists(db_path));
  
  auto conn = sqlite::connect(db_path);
  ASSERT_TRUE(conn);
  
  update_eas_table();
  {
    auto result = exec(conn, "SELECT 1 FROM pragma_table_info('Score') WHERE name='Grade' AND type='CHAR(1)';");
    ASSERT_TRUE(result);
  }
  
  {
    auto result = exec(conn, "SELECT 1 FROM pragma_table_info('Student') WHERE name='Age' AND type='INTEGER';");
    ASSERT_TRUE(result);
  }
  
  {
    auto result = exec(conn, "SELECT 1 WHERE NOT EXISTS (SELECT 1 FROM sqlite_master WHERE type='table' AND name='Major');");
    ASSERT_TRUE(result);
  }
  
  std::filesystem::remove(db_path);
}

}
