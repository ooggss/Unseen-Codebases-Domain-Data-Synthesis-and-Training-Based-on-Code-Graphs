#include <gtest/gtest.h>

#include "test_field_binding.hpp"

namespace test_reaction {

/**
 * Test Case: Bind FieldBase fields to an owner node
 *
 * Test Scenario:
 * - Create domain fields using FieldBase::field
 * - Bind them to an observer node via FieldGraph::bindField
 * - Update multiple fields and ensure notifications cascade to the owner
 */
TEST(reaction, test_field_binding) {
  // ============ Construct Function Inputs ============
  const int initialScore = 42;
  const int scoreDelta = 8;

  // ============ Call Function to Get Return Value ============
  const auto result = test_field_binding(initialScore, scoreDelta);

  // ============ Assert to Verify Return Value ============
  EXPECT_EQ(result.notificationsAfterScoreUpdate, 1);
  EXPECT_EQ(result.notificationsAfterStatusUpdate, 2);
}

}  // namespace test_reaction


