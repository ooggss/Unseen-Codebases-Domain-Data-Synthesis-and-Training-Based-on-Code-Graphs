#include <gtest/gtest.h>

#include "test_logical_expression_builders.hpp"

namespace test_reaction {

/**
 * Test Case: Validate logical expression builders and operators on reactive booleans.
 *
 * Test Scenario:
 * - Create three reactive booleans A, B, C
 * - Build expressions (A && B) and (A && B) || C via expr and logical operators
 * - Flip B from false to true while keeping C false and verify AND/OR outcomes
 */
TEST(reaction, test_logical_expression_builders) {
  const bool a = true;
  const bool b = false;
  const bool c = false;

  const auto snapshot = test_logical_expression_builders(a, b, c);

  EXPECT_FALSE(snapshot.initialAnd);   // true && false
  EXPECT_FALSE(snapshot.initialOr);    // (true && false) || false
  EXPECT_TRUE(snapshot.updatedAnd);    // true && true
  EXPECT_TRUE(snapshot.updatedOr);     // (true && true) || false
}

}  // namespace test_reaction


