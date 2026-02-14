#pragma once

#include <optional>
#include <ranges>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace query_course_enrollment_stats {

struct Course {
  sqlgen::PrimaryKey<int> course_id;
  std::string title;
};

struct Enrollment {
  sqlgen::PrimaryKey<int> enrollment_id;
  sqlgen::ForeignKey<int, Course, "course_id"> course_id;
  std::optional<float> grade;
};

struct CourseStats {
  std::string title;
  int student_count;
  std::optional<double> avg_grade;
};

/**
 * Description: This function calculates enrollment statistics per course, including the number of students and the average grade.
 * Returns: std::vector<CourseStats>.
 */
std::vector<CourseStats> query_course_enrollment_stats() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn_result = sqlite::connect("test_db.sqlite");
  if (!conn_result) return {};
  auto conn = conn_result.value();

  auto query = select_from<Course, "t1">(
                 col<"title", "t1"> | as<"title">, count() | as<"student_count">,
                 avg(col<"grade", "t2">) | as<"avg_grade">) |
               left_join<Enrollment, "t2">(col<"course_id", "t1"> == col<"course_id", "t2">) |
               group_by(col<"course_id", "t1">, col<"title", "t1">);

  auto create_view_op = create_as<CourseStats>(query) | if_not_exists;
  create_view_op(conn);

  std::vector<CourseStats> out = sqlgen::read<std::vector<CourseStats>>(conn).value();
  return out;
}

}  // namespace query_course_enrollment_stats
