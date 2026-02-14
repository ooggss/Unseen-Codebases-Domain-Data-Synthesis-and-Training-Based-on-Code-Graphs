#pragma once

#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>
#include <optional>

namespace full_join_suppliers_products {

struct Supplier {
  sqlgen::PrimaryKey<int> supplier_id;
  std::string name;
};

struct Product {
  sqlgen::PrimaryKey<int> product_id;
  int supplier_id;
  std::string name;
};

struct SupProd {
  std::string supplier_name;
  std::optional<std::string> product_name;
};

/**
 * Returns a vector of SupProd structs, where each struct contains the name of a supplier and the name of a product.
 */
std::vector<SupProd> full_join_suppliers_products() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  auto conn_res = sqlite::connect("test_db.sqlite");
  if (!conn_res) return {};
  auto conn = conn_res.value();

  create_table<Supplier>(conn);
  create_table<Product>(conn);

  const auto query =
      select_from<Supplier, "s">(col<"name", "s"> | as<"supplier_name">,
                                 col<"name", "p"> | as<"product_name">) |
      left_join<Product, "p">(col<"supplier_id", "s"> == col<"supplier_id", "p">) |
      to<std::vector<SupProd>>;
  return query(conn).value();
}

}  // namespace full_join_suppliers_products

