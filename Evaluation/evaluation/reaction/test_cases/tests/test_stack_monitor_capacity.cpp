#include <gtest/gtest.h>

#include "test_stack_monitor_capacity.hpp"

namespace test_reaction {

/**
 * Test Case: Validate StackMonitor::canAllocate (compile-time and runtime).
 *
 * Test Scenario:
 * - Disable monitoring: verify template/runtime checks respect CONDITIONAL_SBO_SIZE
 * - Enable monitoring: verify large allocations succeed until limit, then block
 * - Release guard and ensure runtime allocation succeeds again
 */
TEST(reaction, test_stack_monitor_capacity) {
  constexpr std::size_t runtimeSize = 32;

  const auto snapshot = test_stack_monitor_capacity(runtimeSize);

  EXPECT_TRUE(snapshot.smallAllowedWithoutMonitoring);
  EXPECT_TRUE(snapshot.largeAllowedWithoutMonitoring);
  EXPECT_TRUE(snapshot.runtimeAllowedWithoutMonitoring);
  EXPECT_TRUE(snapshot.largeAllowedWithMonitoring);
  EXPECT_TRUE(snapshot.guardSucceeded);
  EXPECT_TRUE(snapshot.allocationBlockedAtLimit);
  EXPECT_TRUE(snapshot.runtimeAllowedAfterRelease);
}

}  // namespace test_reaction

