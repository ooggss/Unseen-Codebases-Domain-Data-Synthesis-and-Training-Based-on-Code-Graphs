#include <gtest/gtest.h>

#include "test_field_unique_id.hpp"

namespace test_reaction {

/**
 * Test Case: Ensure FieldBase::getId returns stable and unique IDs
 *
 * Test Scenario:
 * - Instantiate two IdTrackedFields objects
 * - Read the ID from the first instance twice to verify stability
 * - Compare against the second instance to ensure uniqueness
 */
TEST(reaction, test_field_unique_id) {
  const auto ids = test_field_unique_id(10, 20);

  EXPECT_EQ(ids.firstIdFirstRead, ids.firstIdSecondRead);
  EXPECT_NE(ids.firstIdFirstRead, ids.secondId);
}

}  // namespace test_reaction


