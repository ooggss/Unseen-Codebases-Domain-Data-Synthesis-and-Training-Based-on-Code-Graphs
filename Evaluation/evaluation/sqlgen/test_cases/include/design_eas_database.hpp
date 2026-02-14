#pragma once

#include <filesystem>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>

namespace test_design_eas_database {

struct Student {
  sqlgen::PrimaryKey<sqlgen::Varchar<10>> SNo;
  sqlgen::Varchar<30> SName;
  std::optional<int> Sex = 1;
  std::optional<sqlgen::DateTime> Birthday;
  std::optional<int> Major;
  std::optional<double> Scorses = 0.0;
  std::optional<std::string> Remark;
};

struct Course {
  sqlgen::PrimaryKey<uint32_t, sqlgen::auto_incr> CID;
  sqlgen::Varchar<30> CName;
  std::optional<int> Term = 1;
  std::optional<int> CTime;
  double CScore = 0.0;
};

struct Score {
  sqlgen::ForeignKey<sqlgen::Varchar<10>, Student, "SNo"> SNo;
  sqlgen::ForeignKey<uint32_t, Course, "CID"> CID;
  std::optional<double> Score;
};

void design_eas_database() {
  const std::string db_path = "test_db.sqlite";

  using namespace sqlgen::literals;

  sqlgen::sqlite::connect(db_path)
      .and_then([](auto&& conn) {
        return sqlgen::exec(conn, "PRAGMA foreign_keys = ON;");
      })
      .and_then(sqlgen::create_table<Student> | sqlgen::if_not_exists)
      .and_then(sqlgen::create_table<Course> | sqlgen::if_not_exists)
      .and_then([](auto&& conn) {
        // Use raw SQL for Score table to handle Composite Primary Key ("SNo", "CID")
        // which is not currently supported via struct attributes in sqlgen::create_table.
        return sqlgen::exec(conn,
                            "CREATE TABLE IF NOT EXISTS \"Score\" ("
                            "\"SNo\" VARCHAR(10) NOT NULL,"
                            "\"CID\" INTEGER NOT NULL,"
                            "\"Score\" REAL,"
                            "PRIMARY KEY(\"SNo\",\"CID\"),"
                            "FOREIGN KEY(\"SNo\") REFERENCES \"Student\"(\"SNo\"),"
                            "FOREIGN KEY(\"CID\") REFERENCES \"Course\"(\"CID\")"
                            ");");
      })
      .value();
}

}
