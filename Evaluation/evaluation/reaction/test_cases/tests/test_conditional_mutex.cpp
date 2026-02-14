#include <gtest/gtest.h>

#include "test_conditional_mutex.hpp"

namespace test_reaction {

/**
 * Test Case: Verify ConditionalMutex try_lock reacts to thread safety toggles.
 *
 * Test Scenario:
 * - Reset ThreadManager for deterministic state
 * - Hold ConditionalMutex via ConditionalLockGuard with safety disabled
 * - Call try_lock (should succeed because locking is a no-op)
 * - Enable thread safety and repeat (try_lock should fail while lock guard holds mutex)
 */
TEST(reaction, test_conditional_mutex_behavior) {
  const auto result = test_conditional_mutex_behavior();

  EXPECT_TRUE(result.tryLockWithoutSafety);
  EXPECT_FALSE(result.tryLockWithSafety);
}

}  // namespace test_reaction

