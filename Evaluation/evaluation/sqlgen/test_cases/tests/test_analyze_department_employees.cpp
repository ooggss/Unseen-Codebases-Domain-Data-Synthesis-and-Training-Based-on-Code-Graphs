#include <gtest/gtest.h>
#include <sqlgen/sqlite.hpp>
#include "analyze_department_employees.hpp"

TEST(sqlite, AnalyzeDepartmentEmployees) {
    using namespace sqlgen;
    using namespace sqlgen::literals;
    // Create sample data
    std::vector<Department> depts = {
        {1, "Engineering", "Building A"},
        {2, "Sales", "Building B"},
        {3, "Marketing", "Building C"} // Department with no employees
    };

    std::vector<Employee> emps = {
        {1, 1, "John", "Doe", 80000.0}, // In Engineering
        {2, 1, "Jane", "Smith", 85000.0}, // In Engineering
        {3, 2, "Bob", "Johnson", 70000.0}, // In Sales
        {4, 4, "Alice", "Williams", 75000.0} // In Department 4 (does not exist)
    };
    auto conn = sqlite::connect("test_db.sqlite")
        .and_then(drop<Department> | if_exists)
        .and_then(drop<Employee> | if_exists)
        .and_then(create_table<Department>)
        .and_then(create_table<Employee>)
        .and_then(insert(depts))
        .and_then(insert(emps))
        .value();

    auto analysis = analyze_department_employees();

    // 1. Verify INNER JOIN
    // Should return 3 records (John, Jane, Bob) - Alice has invalid dept, Marketing has no employees
    ASSERT_EQ(analysis.inner_join_results.size(), 3);
    for (const auto& res : analysis.inner_join_results) {
        EXPECT_TRUE(res.department_name.has_value());
        EXPECT_TRUE(res.first_name.has_value());
        EXPECT_TRUE(res.last_name.has_value());
        EXPECT_TRUE(res.salary.has_value());
    }

    // 2. Verify LEFT JOIN (Employees LEFT JOIN Departments)
    // Should return all 4 employees. Alice will have null department info.
    ASSERT_EQ(analysis.left_join_results.size(), 4);
    bool found_alice = false;
    for (const auto& res : analysis.left_join_results) {
        if (res.first_name.value_or("") == "Alice") {
            found_alice = true;
            EXPECT_FALSE(res.department_name.has_value()); // No matching department
        } else {
            EXPECT_TRUE(res.department_name.has_value());
        }
    }
    EXPECT_TRUE(found_alice);

    // 3. Verify RIGHT JOIN (Employees RIGHT JOIN Departments)
    ASSERT_EQ(analysis.right_join_results.size(), 4);
    bool found_marketing = false;
    for (const auto& res : analysis.right_join_results) {
        if (res.department_name.value_or("") == "Marketing") {
            found_marketing = true;
            EXPECT_FALSE(res.first_name.has_value());
            EXPECT_FALSE(res.last_name.has_value());
            EXPECT_FALSE(res.salary.has_value());
        }
    }
    EXPECT_TRUE(found_marketing);

    // 4. Verify FULL JOIN
    ASSERT_EQ(analysis.full_join_results.size(), 5);
    int null_dept_count = 0;
    int null_emp_count = 0;
    for (const auto& res : analysis.full_join_results) {
        if (!res.department_name.has_value()) null_dept_count++;
        if (!res.first_name.has_value()) null_emp_count++;
    }
    EXPECT_EQ(null_dept_count, 1); // Alice
    EXPECT_EQ(null_emp_count, 1); // Marketing
}
