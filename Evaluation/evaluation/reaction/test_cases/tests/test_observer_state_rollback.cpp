#include <gtest/gtest.h>

#include "test_observer_state_rollback.hpp"

namespace test_reaction {

/**
 * Test Case: Validate transactional dependency updates with rollback support
 *
 * Test Scenario:
 * - Register initial dependency graph (aggregator observes sensor A)
 * - Replace dependencies using updateObserversTransactional (observe sensor B)
 * - Roll back to saved state and ensure sensor A notifications resume
 */
TEST(reaction, test_observer_state_rollback) {
  // ============ Call Function to Get Return Value ============
  const auto result = test_observer_state_rollback();

  // ============ Assert to Verify Return Value ============
  EXPECT_EQ(result.notificationsAfterSecondBinding, 1);
  EXPECT_EQ(result.notificationsAfterRollback, 2);
}

}  // namespace test_reaction


