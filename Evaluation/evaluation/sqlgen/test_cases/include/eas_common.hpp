#pragma once

#include <filesystem>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>

using namespace sqlgen::literals;

struct Student {
  sqlgen::PrimaryKey<sqlgen::Varchar<10>> SNo;
  sqlgen::Varchar<30> SName;
  int Sex = 1;
  std::optional<sqlgen::DateTime> Birthday;
  std::optional<uint32_t> Major;
  std::optional<double> Scorses = 0.0;
  std::optional<std::string> Remark;
};

struct Course {
  sqlgen::PrimaryKey<uint32_t, sqlgen::auto_incr> CID;
  sqlgen::Varchar<50> CName;
  std::optional<int> Term = 1;
  std::optional<int> CTime;
  int Credit = 0;
};

struct Score {
  sqlgen::PrimaryKey<uint32_t, sqlgen::auto_incr> ScID;
  sqlgen::ForeignKey<sqlgen::Varchar<10>, Student, "SNo"> SNo;
  sqlgen::ForeignKey<uint32_t, Course, "CID"> CID;
  std::optional<double> Score;
};

struct Major {
  sqlgen::PrimaryKey<uint32_t> MID;
  sqlgen::Varchar<30> MName;
};

const std::string db_path = "test_db.sqlite";

void design_eas_database_without_major() {
  std::filesystem::create_directories("data");
  sqlgen::sqlite::connect(db_path)
      .and_then([](auto&& conn) {
        return sqlgen::exec(conn, "PRAGMA foreign_keys = ON;");
      })
      .and_then(sqlgen::create_table<Student> | sqlgen::if_not_exists)
      .and_then(sqlgen::create_table<Course> | sqlgen::if_not_exists)
      .and_then(sqlgen::create_table<Score> | sqlgen::if_not_exists)
      .value();
}

void design_eas_database_with_major() {
  design_eas_database_without_major();

  sqlgen::sqlite::connect(db_path)
      .and_then(sqlgen::create_table<Major> | sqlgen::if_not_exists)
      .value();
}

const auto student_records = std::vector<Student>{
    Student{"S001", "Hua Li", 1, std::nullopt, 1, std::nullopt, std::nullopt},
    Student{"S002", "Sunnee", 2, std::nullopt, 2, std::nullopt, std::nullopt},
    Student{"S003", "Jessica", 1, std::nullopt, 3, std::nullopt, std::nullopt},
};

const auto major_records = std::vector<Major>{
    Major{1, "Computer Science"},
    Major{2, "Physics"},
    Major{3, "History"},
};

const auto course_records = std::vector<Course>{
    Course{ .CName = "Introduction to Computer Science", .Term = 1, .CTime = 30, .Credit = 2},
    Course{ .CName = "Physics 101", .Term = 2, .CTime = std::nullopt, .Credit = 2},
    Course{ .CName = "History of World", .Term = 2, .CTime = std::nullopt, .Credit = 2},
};

const auto score_records = std::vector<Score>{
    Score{ .SNo = "S001", .CID = 1, .Score = 80.0},
    Score{ .SNo = "S001", .CID = 2, .Score = 90.0},
    Score{ .SNo = "S002", .CID = 2, .Score = 75.0},
    Score{ .SNo = "S002", .CID = 1, .Score = 85.0},
    Score{ .SNo = "S003", .CID = 3, .Score = 95.0},
};

void build_eas_database() {
  design_eas_database_with_major();
  // Add records to table
  const auto conn = sqlgen::sqlite::connect(db_path);
  conn.and_then(sqlgen::insert(student_records))
      .and_then(sqlgen::insert(major_records))
      .and_then(sqlgen::insert(course_records))
      .and_then(sqlgen::insert(score_records))
      .value();
}
