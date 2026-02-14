#include <gtest/gtest.h>

#include "test_stack_monitor_limits.hpp"

namespace test_reaction {

/**
 * Test Case: Verify StackMonitor usage stats reflect guard allocations.
 *
 * Test Scenario:
 * - Enable monitoring and capture stats before allocation
 * - Acquire a large StackGuard and ensure template/runtime checks respond accordingly
 * - Compare usage stats before vs after the guard
 */
TEST(reaction, test_stack_monitor_limits) {
  const auto snapshot = test_stack_monitor_limits();

  EXPECT_TRUE(snapshot.templateAllocationAllowed);
  EXPECT_TRUE(snapshot.runtimeAllocationAllowed);
  EXPECT_TRUE(snapshot.guardHeld);
  EXPECT_TRUE(snapshot.allocationBlockedWhileGuardHeld);
  EXPECT_LE(snapshot.statsBeforeGuard.current_usage, snapshot.statsAfterGuard.current_usage);
  EXPECT_GE(snapshot.statsAfterGuard.current_usage,
            snapshot.statsBeforeGuard.current_usage);
}

}  // namespace test_reaction

