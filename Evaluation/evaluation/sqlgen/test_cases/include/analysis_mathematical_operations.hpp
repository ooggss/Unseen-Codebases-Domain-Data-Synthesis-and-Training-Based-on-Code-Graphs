#pragma once

#include <cmath>
#include <sqlgen.hpp>
#include <sqlgen/sqlite.hpp>
#include <vector>

namespace mathematical_operations_analysis {

struct Product {
  sqlgen::PrimaryKey<int> product_id;
  std::string name;
  double price;
  int quantity;
  double discount_rate;
};

struct MathAnalysis {
  int product_id;
  std::string name;
  double abs_price;
  double ceil_price;
  double floor_price;
  double rounded_price;
  double exp_discount;
  double ln_price;
  double log2_quantity;
  double sin_discount;
  double cos_discount;
  double tan_discount;
  double sqrt_quantity;
};

/**
 * Insert products into a temporary SQLite table and run a SELECT that computes
 * various mathematical expressions, returning results as std::vector<MathAnalysis>.
 */
std::vector<MathAnalysis> analyze_mathematical_operations() {
  using namespace sqlgen;
  using namespace sqlgen::literals;

  const auto query =
      select_from<Product>(
          cast<int>("product_id"_c).as<"product_id">(), "name"_c, abs("price"_c).as<"abs_price">(),
          ceil("price"_c).as<"ceil_price">(),
          floor("price"_c).as<"floor_price">(),
          round("price"_c, 2).as<"rounded_price">(),
          exp("discount_rate"_c / 100.0).as<"exp_discount">(),
          ln("price"_c).as<"ln_price">(),
          log2(cast<double>("quantity"_c)).as<"log2_quantity">(),
          sin("discount_rate"_c).as<"sin_discount">(),
          cos("discount_rate"_c).as<"cos_discount">(),
          tan("discount_rate"_c).as<"tan_discount">(),
          sqrt(cast<double>("quantity"_c)).as<"sqrt_quantity">()) |
      to<std::vector<MathAnalysis>>;

  return sqlite::connect("test_db.sqlite")
      .and_then(query)
      .value();
}

}  // namespace mathematical_operations_analysis
