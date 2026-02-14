#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>
#include <optional>

namespace right_join_departments_projects {

struct Department {
  sqlgen::PrimaryKey<int> department_id;
  std::string name;
};

struct Project {
  sqlgen::PrimaryKey<int> project_id;
  int department_id;
  std::string name;
};

struct DepProj {
  std::string department_name;
  std::optional<std::string> project_name;
};

/**
 * This function demonstrates how to perform a right join between departments and projects using sqlgen read API.
 * Returns: std::vector<DepProj>, where each struct contains the department name (if available) and the project name.
 */
std::vector<DepProj> right_join_departments_projects() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn = sqlite::connect("test_db.sqlite").value();

  const auto query =
      select_from<Project, "p">(col<"name", "d"> | as<"department_name">,
                                col<"name", "p"> | as<"project_name">) |
      right_join<Department, "d">(col<"department_id", "p"> == col<"department_id", "d">) |
      to<std::vector<DepProj>>;
  // const auto query =
  //     select_from<Project, "p">(col<"name", "d"> | as<"department_name">,
  //                               col<"name", "p"> | as<"project_name">) |
  //     left_join<Department, "d">(col<"department_id", "p"> == col<"department_id", "d">) |
  //     to<std::vector<DepProj>>;
  return query(conn).value();
}

}  // namespace right_join_departments_projects

