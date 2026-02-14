#include <gtest/gtest.h>

#include "test_stack_monitor.hpp"

namespace test_reaction {

/**
 * Test Case: Validate StackMonitor usage tracking and monitoring toggles.
 *
 * Test Scenario:
 * - Reset monitoring state and initialize StackMonitor
 * - Enter a guard scope and inspect usage counters
 * - Disable monitoring again and ensure counters drop to zero
 */
TEST(reaction, test_stack_monitor_guard) {
  const auto report = test_stack_monitor_guard();

  EXPECT_TRUE(report.monitoringEnabledBefore);
  EXPECT_TRUE(report.guardAllocated);
  EXPECT_EQ(report.usageDuringGuard, 256u);
  EXPECT_EQ(report.usageAfterGuard, 0u);
  EXPECT_GT(report.usagePercentage, 0.0);
  EXPECT_FALSE(report.nearLimitDuringGuard);
  EXPECT_FALSE(report.monitoringAfterDisable);
}

}  // namespace test_reaction

