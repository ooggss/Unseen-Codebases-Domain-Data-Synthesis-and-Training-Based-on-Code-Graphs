#include <gtest/gtest.h>

#include "test_thread_manager_multithread.hpp"

namespace test_reaction {

/**
 * Test Case: Ensure thread manager enables safety after multi-thread registration
 *
 * Test Scenario:
 * - Reset thread manager state
 * - Register current thread and capture status
 * - Spawn an additional thread that registers itself
 * - Verify thread count and safety flags flip after multi-thread detection
 */
TEST(reaction, test_thread_manager_multithread) {
  const auto status = test_thread_manager_multithread();

  EXPECT_FALSE(status.safetyBefore);
  EXPECT_EQ(status.threadCountBefore, 1);
  EXPECT_TRUE(status.safetyAfter);
  EXPECT_EQ(status.threadCountAfter, 2);
}

}  // namespace test_reaction


