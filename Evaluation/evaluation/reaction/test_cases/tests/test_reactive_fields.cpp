#include <gtest/gtest.h>

#include "test_reactive_fields.hpp"

namespace test_reaction {

/**
 * Test Case: Test reactive fields functionality
 *
 * Test Scenario:
 * - Create a reactive PersonRecord with name and age fields
 * - Build a calculation that reads reactive fields
 * - Update fields and verify calculation output changes
 */
TEST(reaction, test_reactive_fields) {
  // ============ Construct Function Inputs ============

  const std::string initialName = "Alice";
  const int initialAge = 30;
  const std::string newName = "Alice Johnson";
  const int newAge = 35;

  // ============ Call Function to Get Return Value ============
  const std::string info =
      test_reactive_fields(initialName, initialAge, newName, newAge);

  // ============ Assert to Verify Return Value ============

  EXPECT_EQ(info, "Alice Johnson@35");
}

}  // namespace test_reaction

