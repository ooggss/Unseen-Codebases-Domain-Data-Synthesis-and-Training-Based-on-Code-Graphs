#include <gtest/gtest.h>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <filesystem>
#include "design_eas_database.hpp"

namespace test_design_eas_database {

  TEST(sqlite, test_design_eas_database) {
    // Clean up database before running test
    const std::string db_path = "test_db.sqlite";
    if (std::filesystem::exists(db_path)) {
      std::filesystem::remove(db_path);
    }

    design_eas_database();

    ASSERT_TRUE(std::filesystem::exists(db_path));

    const auto conn = sqlgen::sqlite::connect(db_path);
    ASSERT_TRUE(conn);

    auto has_table = [&](const std::string& name) {
      const auto res = sqlgen::exec(conn, "SELECT name FROM sqlite_master WHERE type='table' AND name='" + name + "';");
      return res.has_value();
    };

    ASSERT_TRUE(has_table("Student"));
    ASSERT_TRUE(has_table("Course"));
    ASSERT_TRUE(has_table("Score"));

    // Helper to check column existence
    auto has_column = [&](const std::string& table, const std::string& column) {
      const auto res = sqlgen::exec(conn, "SELECT 1 WHERE EXISTS("
        "SELECT 1 FROM pragma_table_info('" + table + "') WHERE name='" + column + "');");
      return res.has_value();
    };

    // Verify Student table columns
    ASSERT_TRUE(has_column("Student", "SNo"));
    ASSERT_TRUE(has_column("Student", "SName"));
    ASSERT_TRUE(has_column("Student", "Sex"));
    ASSERT_TRUE(has_column("Student", "Birthday"));
    ASSERT_TRUE(has_column("Student", "Major"));
    ASSERT_TRUE(has_column("Student", "Scorses"));
    ASSERT_TRUE(has_column("Student", "Remark"));

    // Verify Course table columns
    ASSERT_TRUE(has_column("Course", "CID"));
    ASSERT_TRUE(has_column("Course", "CName"));
    ASSERT_TRUE(has_column("Course", "Term"));
    ASSERT_TRUE(has_column("Course", "CTime"));
    ASSERT_TRUE(has_column("Course", "CScore"));

    // Verify Score table columns
    ASSERT_TRUE(has_column("Score", "SNo"));
    ASSERT_TRUE(has_column("Score", "CID"));
    ASSERT_TRUE(has_column("Score", "Score"));

    // Verify constraints
    // Check SNo is Primary Key in Student
    {
      const auto res = sqlgen::exec(conn, "SELECT 1 FROM pragma_table_info('Student') WHERE name='SNo' AND pk=1;");
      ASSERT_TRUE(res);
    }

    // Check CID is Primary Key in Course
    {
      const auto res = sqlgen::exec(conn, "SELECT 1 FROM pragma_table_info('Course') WHERE name='CID' AND pk=1;");
      ASSERT_TRUE(res);
    }

    // Check Composite Primary Key in Score (SNo and CID both pk > 0)
    {
      const auto res_sno = sqlgen::exec(conn, "SELECT 1 FROM pragma_table_info('Score') WHERE name='SNo' AND pk > 0;");
      ASSERT_TRUE(res_sno);
      const auto res_cid = sqlgen::exec(conn, "SELECT 1 FROM pragma_table_info('Score') WHERE name='CID' AND pk > 0;");
      ASSERT_TRUE(res_cid);
    }

    // Verify Foreign Keys
    {
      const auto res = sqlgen::exec(conn, "SELECT 1 FROM pragma_foreign_key_list('Score') WHERE \"table\"='Student' AND \"from\"='SNo' AND \"to\"='SNo';");
      ASSERT_TRUE(res);
    }
    {
      const auto res = sqlgen::exec(conn, "SELECT 1 FROM pragma_foreign_key_list('Score') WHERE \"table\"='Course' AND \"from\"='CID' AND \"to\"='CID';");
      ASSERT_TRUE(res);
    }

    std::filesystem::remove(db_path);
  }

}
