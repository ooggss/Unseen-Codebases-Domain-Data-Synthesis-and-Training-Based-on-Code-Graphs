#include <gtest/gtest.h>

#include "test_thread_manager_manual.hpp"

namespace test_reaction {

/**
 * Test Case: Manually enable and reset thread safety mode
 *
 * Test Scenario:
 * - Reset ThreadManager state
 * - Register current thread and verify safety is still disabled
 * - Call enableThreadSafety() explicitly
 * - Reset again and confirm safety flag is cleared
 */
TEST(reaction, test_thread_manager_manual) {
  const auto transition = test_thread_manager_manual();

  EXPECT_FALSE(transition.beforeEnable);
  EXPECT_TRUE(transition.afterEnable);
  EXPECT_FALSE(transition.afterReset);
  EXPECT_EQ(transition.threadCount, 1);
}

}  // namespace test_reaction


