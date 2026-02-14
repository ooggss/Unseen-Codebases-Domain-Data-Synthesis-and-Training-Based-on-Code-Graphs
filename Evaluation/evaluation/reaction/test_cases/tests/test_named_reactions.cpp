#include <gtest/gtest.h>

#include "test_named_reactions.hpp"

namespace test_reaction {

/**
 * Test Case: Test naming and retrieving reactive node names
 *
 * Test Scenario:
 * - Create reactive variables and calculations
 * - Assign names using setName()
 * - Retrieve names using getName() and verify
 */
TEST(reaction, test_named_reactions) {
  // ============ Construct Function Inputs ============

  const int valueA = 3;
  const int valueB = 7;

  // ============ Call Function to Get Return Value ============
  const std::string names = test_named_reactions(valueA, valueB);

  // ============ Assert to Verify Return Value ============

  EXPECT_EQ(names, "input_a|input_b|sum_calc|double_calc|logger_action");
}

}  // namespace test_reaction

