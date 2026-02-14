#include <gtest/gtest.h>
#include "right_join_departments_projects.hpp"

namespace right_join_departments_projects {

TEST(sqlite, right_join_departments_projects) {
  using namespace sqlgen;
  auto conn = sqlite::connect("test_db.sqlite").value();
  drop<Department>(conn);
  drop<Project>(conn);
  create_table<Department>(conn);
  create_table<Project>(conn);
  std::vector<Department> departments = {
    {1, "D1"}, {2, "D2"}, {3, "D3"},
  };
  std::vector<Project> projects = {
    {1, 1, "P1"}, {2, 2, "P2"}
  };
  insert(conn, departments);
  insert(conn, projects);

  auto rows = right_join_departments_projects();
  ASSERT_GE(rows.size(), 3);
}

}  // namespace right_join_departments_projects

