#include <gtest/gtest.h>

#include <filesystem>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>

#include "add+modify_eas_records.hpp"
#include "eas_common.hpp"
using namespace sqlgen;
using namespace sqlgen::literals;

namespace test_add_modify_eas_records {

TEST(sqlite, test_add_modify_eas_records) {
  design_eas_database_with_major();

  const std::string db_path = "test_db.sqlite";
  ASSERT_TRUE(std::filesystem::exists(db_path));

  std::vector<Student> student_records = {
      Student{"S001", "Li Hua", 1, std::nullopt, 1, std::nullopt, std::nullopt},
      Student{"S002", "Anne", 2, std::nullopt, 2, std::nullopt, std::nullopt}
  };
  
  add_eas_records("Student", student_records);
  auto conn = sqlite::connect(db_path);
  ASSERT_TRUE(conn);
  
  {
    const auto query = sqlgen::read<std::vector<Student>>;
    const auto student1 = conn.and_then(query).value();
    ASSERT_TRUE(student1.size() == 2);
  
    const auto json1 = rfl::json::write(student1);
    const auto json2 = rfl::json::write(student_records);
    EXPECT_EQ(json2, json1);
  }
  
  {
    auto result = exec(conn, "SELECT * FROM Student WHERE SNo='S002';");
    ASSERT_TRUE(result);
    
    auto check_result = exec(conn, "SELECT COUNT(*) as cnt FROM Student WHERE SNo='S002' AND SName='Anne' AND Sex=2 AND Major=2;");
    ASSERT_TRUE(check_result);
  }
  
  // modify_eas_records_by_id("Student", "S001", "Scorses", 90.0);
  
  // {
  //   const auto query = select_from<Student>("Scorses") | where("SNo"_c == "S001");
  //   const auto scorses = conn.and_then(query | to<std::vector<double>>).value();
  //   ASSERT_TRUE(scorses.size() == 1);
  //   EXPECT_EQ(scorses[0], 90.0);
  // }
  
  delete_eas_records_by_id("Student", "S002");
  
  {
    const auto query = sqlgen::read<std::vector<Student>> | where("SNo"_c == "S002");
    const auto student2 = conn.and_then(query).value();
    ASSERT_TRUE(student2.size() == 0);
  }
  
  std::filesystem::remove(db_path);
}

}
