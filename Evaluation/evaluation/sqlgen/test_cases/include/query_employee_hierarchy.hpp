#pragma once

#include <optional>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace query_employee_hierarchy {

struct Employee {
  sqlgen::PrimaryKey<int> emp_id;
  std::string name;
  std::optional<int> manager_id;
};

struct EmployeeManager {
  std::string employee;
  std::optional<std::string> manager;
};

/**
 * Description: retrieve employee details along with their manager's name using a left join.
 * Returns: std::vector<EmployeeManager>, where each struct contains the employee's name and their manager's name (if any).
 */
std::vector<EmployeeManager> query_employee_hierarchy() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn_res = sqlite::connect("test_db.sqlite");
  if (!conn_res) return {};
  auto conn = conn_res.value();

  create_table<Employee>(conn);

  const auto q =
      select_from<Employee, "t1">("name"_t1.as<"employee">(),
                                  "name"_t2.as<"manager">()) |
      left_join<Employee, "t2">("manager_id"_t1 == "emp_id"_t2) |
      to<std::vector<EmployeeManager>>;

  return q(conn).value();
}

}  // namespace query_employee_hierarchy
