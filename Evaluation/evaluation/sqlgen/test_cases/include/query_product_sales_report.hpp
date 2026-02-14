#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace query_product_sales_report {

struct Product {
  sqlgen::PrimaryKey<int> product_id;
  std::string category;
};

struct Sale {
  sqlgen::PrimaryKey<int> sale_id;
  int product_id;
  int quantity;
  double amount;
};

struct CategoryReport {
  std::string category;
  int total_qty;
  double total_amt;
};

/**
 * Function: Generate a sales report by product category.
 * @return vector<CategoryReport>
 */
std::vector<CategoryReport> query_product_sales_report() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn_res = sqlite::connect("test_db.sqlite");
  if (!conn_res) return {};
  auto conn = conn_res.value();

  create_table<Product>(conn);
  create_table<Sale>(conn);

  std::string view_sql = R"(
    CREATE VIEW IF NOT EXISTS CategoryReport AS
    SELECT p.category AS category,
           SUM(s.quantity) AS total_qty,
           SUM(s.amount) AS total_amt
    FROM Product p
    INNER JOIN Sale s ON p.product_id = s.product_id
    GROUP BY p.category
    HAVING SUM(s.amount) > 5000.0;
  )";
  exec(conn, view_sql);

  std::vector<CategoryReport> out = sqlgen::read<std::vector<CategoryReport>>(conn).value();
  return out;
}

}  // namespace query_product_sales_report
