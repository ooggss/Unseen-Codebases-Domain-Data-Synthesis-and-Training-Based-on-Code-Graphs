#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>
#include <optional>

struct Department {
  sqlgen::PrimaryKey<int> department_id;
  std::string department_name;
  std::string location;
};

struct Employee {
  sqlgen::PrimaryKey<int> employee_id;
  int department_id;
  std::string first_name;
  std::string last_name;
  double salary;
};

struct JoinResult {
  std::optional<std::string> department_name;
  std::optional<std::string> first_name;
  std::optional<std::string> last_name;
  std::optional<double> salary;
};

struct JoinAnalysis {
  std::vector<JoinResult> inner_join_results;
  std::vector<JoinResult> left_join_results;
  std::vector<JoinResult> right_join_results;
  std::vector<JoinResult> full_join_results;
};

/**
 * Provides data-join analysis between Department and Employee input collections by
 * creating temporary SQL tables, inserting the provided rows, and executing a
 * variety of join queries to produce join-output samples.
 * Returns: JoinAnalysis.
 */
JoinAnalysis analyze_department_employees() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn = sqlite::connect("test_db.sqlite").value();

  // INNER JOIN
  const auto inner_join_res = (select_from<Department, "d">(
          col<"department_name", "d">.as<"department_name">(), 
          col<"first_name", "e">.as<"first_name">(), 
          col<"last_name", "e">.as<"last_name">(), 
          col<"salary", "e">.as<"salary">()) |
      inner_join<Employee, "e">(col<"department_id", "d"> == col<"department_id", "e">) | 
      to<std::vector<JoinResult>>)(conn).value();

  // LEFT JOIN
  const auto left_join_res = (select_from<Department, "d">(
          col<"department_name", "d">.as<"department_name">(), 
          col<"first_name", "e">.as<"first_name">(), 
          col<"last_name", "e">.as<"last_name">(), 
          col<"salary", "e">.as<"salary">()) |
      left_join<Employee, "e">(col<"department_id", "d"> == col<"department_id", "e">) | 
      to<std::vector<JoinResult>>)(conn).value();
   
   const auto right_join_res = left_join_res; 
   
   // For "LEFT JOIN" requirement (All Employees, even if no Department):
   const auto real_left_join_res = (select_from<Employee, "e">(
           col<"department_name", "d">.as<"department_name">(), 
           col<"first_name", "e">.as<"first_name">(), 
           col<"last_name", "e">.as<"last_name">(), 
           col<"salary", "e">.as<"salary">()) |
       left_join<Department, "d">(col<"department_id", "e"> == col<"department_id", "d">) | 
       to<std::vector<JoinResult>>)(conn).value();
       
   // FULL JOIN
   std::vector<JoinResult> full_join_combined = real_left_join_res;
   for (const auto& r_res : right_join_res) {
       bool found = false;
       for (const auto& l_res : real_left_join_res) {
           if (r_res.department_name == l_res.department_name && 
               r_res.first_name == l_res.first_name &&
               r_res.last_name == l_res.last_name &&
               r_res.salary == l_res.salary) {
               found = true;
               break;
           }
       }
       if (!found) {
           full_join_combined.push_back(r_res);
       }
   }
   
   const auto full_join_res = full_join_combined;

  return JoinAnalysis{
    .inner_join_results = inner_join_res,
    .left_join_results = real_left_join_res,
    .right_join_results = right_join_res,
    .full_join_results = full_join_res
  };
}
