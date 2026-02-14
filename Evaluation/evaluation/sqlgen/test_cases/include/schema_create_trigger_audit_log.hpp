#pragma once

#include <ranges>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace schema_create_trigger_audit_log {


struct Product {
  sqlgen::PrimaryKey<int> product_id;
  std::string name;
  double price;
  int stock;
};

struct AuditLog {
  sqlgen::PrimaryKey<int, sqlgen::auto_incr> log_id;
  std::string table_name;
  int record_id;
  std::string action;
  sqlgen::DateTime timestamp;
};


/**
 * Function: Create a trigger for auditing changes on Product table.
 * @return true if trigger creation succeeds, false otherwise
 */
bool create_trigger_audit_log() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn_result = sqlite::connect("test_db.sqlite");
  if (!conn_result) return false;
  auto conn = conn_result.value();

  // Create tables if they don't exist (helper for standalone run, though test might do it)
  create_table<Product>(conn);
  create_table<AuditLog>(conn);

  // Execute raw SQL to create the trigger
  std::string trigger_sql = R"(
    CREATE TRIGGER IF NOT EXISTS audit_product_update
    AFTER UPDATE ON Product
    BEGIN
        INSERT INTO AuditLog (table_name, record_id, action, timestamp)
        VALUES ('Product', OLD.product_id, 'UPDATE', CURRENT_TIMESTAMP);
    END;
  )";

  auto res = exec(conn, trigger_sql);
  
  return res.has_value();
}

}  // namespace schema_create_trigger_audit_log
