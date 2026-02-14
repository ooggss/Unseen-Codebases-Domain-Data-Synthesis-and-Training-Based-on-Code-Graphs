#include <gtest/gtest.h>

#include "test_thread_guard.hpp"

namespace test_reaction {

/**
 * Test Case: Ensure ThreadRegistrationGuard triggers thread safety mode
 *
 * Test Scenario:
 * - Reset ThreadManager to single-thread state
 * - Spawn a worker that instantiates ThreadRegistrationGuard
 * - Verify thread safety toggles on and thread count reflects two threads
 */
TEST(reaction, test_thread_guard) {
  const auto state = test_thread_guard();

  EXPECT_FALSE(state.safetyBeforeGuard);
  EXPECT_EQ(state.threadCountBeforeGuard, 1);
  EXPECT_TRUE(state.safetyAfterGuard);
  EXPECT_EQ(state.threadCountAfterGuard, 2);
}

}  // namespace test_reaction


