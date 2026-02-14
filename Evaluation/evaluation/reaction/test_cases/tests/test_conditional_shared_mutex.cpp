#include <gtest/gtest.h>

#include "test_conditional_shared_mutex.hpp"

namespace test_reaction {

/**
 * Test Case: Verify ConditionalSharedMutex toggles behavior with thread safety.
 *
 * Test Scenario:
 * - Attempt try_lock_shared/try_lock before enabling safety (should succeed)
 * - Enable safety, hold shared lock, and ensure try_lock fails while lock is held
 */
TEST(reaction, test_conditional_shared_mutex) {
  const auto result = test_conditional_shared_mutex();

  EXPECT_TRUE(result.trySharedWithoutSafety);
  EXPECT_TRUE(result.tryUniqueWhileSharedWithoutSafety);
  EXPECT_TRUE(result.trySharedWithSafety);
  EXPECT_FALSE(result.tryUniqueWhileSharedWithSafety);
}

}  // namespace test_reaction

