#include <gtest/gtest.h>
#include <sqlgen/sqlite.hpp>
#include "analysis_mathematical_operations.hpp"
#include <cmath>

using namespace mathematical_operations_analysis;

TEST(sqlite, AnalyzeMathematicalOperations) {
  using namespace sqlgen;
  using namespace sqlgen::literals;
  auto conn = sqlite::connect("test_db.sqlite").value();
  drop<Product>(conn);
  create_table<Product>(conn);

  // Insert sample data
  std::vector<Product> products = {
      {1, "Laptop", 999.99, 10, 15.5},
      {2, "Mouse", 25.50, 100, 5.0},
      {3, "Keyboard", 150.75, 50, 10.0}
  };
  insert(conn, products);
    
  auto results = analyze_mathematical_operations();
  ASSERT_EQ(results.size(), 3);

  // Verify Laptop data
  const auto& laptop = results[0];
  EXPECT_EQ(laptop.product_id, 1);
  EXPECT_EQ(laptop.name, "Laptop");
  
  // Basic math checks
  EXPECT_DOUBLE_EQ(laptop.abs_price, 999.99);
  EXPECT_DOUBLE_EQ(laptop.ceil_price, 1000.0);
  EXPECT_DOUBLE_EQ(laptop.floor_price, 999.0);
  EXPECT_DOUBLE_EQ(laptop.rounded_price, 999.99);
  
  // Exponential and Logarithmic checks
  // Using NEAR for floating point comparisons with calculations
  EXPECT_NEAR(laptop.exp_discount, std::exp(15.5/100.0), 1e-6);
  EXPECT_NEAR(laptop.ln_price, std::log(999.99), 1e-6);
  EXPECT_NEAR(laptop.log2_quantity, std::log2(10), 1e-6);
  
  // Trigonometric checks
  EXPECT_NEAR(laptop.sin_discount, std::sin(15.5), 1e-6);
  EXPECT_NEAR(laptop.cos_discount, std::cos(15.5), 1e-6);
  EXPECT_NEAR(laptop.tan_discount, std::tan(15.5), 1e-6);
  
  // Sqrt check
  EXPECT_NEAR(laptop.sqrt_quantity, std::sqrt(10), 1e-6);

  // Verify Mouse data
  const auto& mouse = results[1];
  EXPECT_EQ(mouse.product_id, 2);
  EXPECT_DOUBLE_EQ(mouse.abs_price, 25.50);
  EXPECT_DOUBLE_EQ(mouse.ceil_price, 26.0);
  EXPECT_DOUBLE_EQ(mouse.floor_price, 25.0);
  
  // Verify Keyboard data
  const auto& keyboard = results[2];
  EXPECT_EQ(keyboard.product_id, 3);
  EXPECT_DOUBLE_EQ(keyboard.abs_price, 150.75);
}
