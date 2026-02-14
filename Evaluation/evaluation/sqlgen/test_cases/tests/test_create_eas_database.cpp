#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>

#include "create_eas_database.hpp"

namespace test_create_eas_database {

/**
 * Test Case: Create EAS (Educational Administration System) database
 * 
 * Test Scenario:
 * 1. Call create_eas_database() function to create the database
 * 2. Check if the file test_db.sqlite exists
 * 3. Check if the file is readable
 * 4. Connect to the database and verify it contains the EAS_DB database
 * 5. Cleanup: delete the test database file
 */
TEST(sqlite, test_create_eas_database) {
    create_eas_database();
    
    const std::string db_path = "test_db.sqlite";
    
    ASSERT_TRUE(std::filesystem::exists(db_path)) 
        << "Database file " << db_path << " does not exist";
    
    std::ifstream file(db_path, std::ios::binary);
    ASSERT_TRUE(file.good()) 
        << "Cannot read database file " << db_path;
    file.close();
    
    const auto conn = sqlgen::sqlite::connect(db_path);
    ASSERT_TRUE(conn) 
        << "Unable to connect to database";
    
    const auto result = sqlgen::exec(conn, "PRAGMA database_list;");
    ASSERT_TRUE(result) 
        << "Unable to execute PRAGMA database_list query";
    
    const auto check_result = sqlgen::exec(conn, "SELECT name FROM pragma_database_list WHERE name='EAS_DB';");
    ASSERT_TRUE(check_result) 
        << "Database does not contain EAS_DB";
    
    std::filesystem::remove(db_path);
}

}