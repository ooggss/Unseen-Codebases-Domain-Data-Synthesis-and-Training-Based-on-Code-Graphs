#include <gtest/gtest.h>

#include "test_global_state_scoped_guards.hpp"

namespace test_reaction {

/**
 * Test Case: Validate ScopedValue-based global state guards and query helpers.
 *
 * Test Scenario:
 * - resetGlobalState() to clear any previous registration/batch state
 * - Enter RegFunGuard/BatchFunGuard/BatchExeGuard scopes and verify corresponding flags flip
 * - After all guards are destroyed and resetGlobalState() is called again, all flags return false
 */
TEST(reaction, test_global_state_scoped_guards) {
  const auto snapshot = test_global_state_scoped_guards();

  EXPECT_FALSE(snapshot.trackingActiveBefore);
  EXPECT_FALSE(snapshot.batchActiveBefore);
  EXPECT_FALSE(snapshot.batchFunActiveBefore);

  EXPECT_TRUE(snapshot.trackingActiveInRegGuard);
  EXPECT_TRUE(snapshot.batchFunActiveInBatchGuard);
  EXPECT_TRUE(snapshot.batchActiveInBatchExeGuard);

  EXPECT_FALSE(snapshot.trackingActiveAfter);
  EXPECT_FALSE(snapshot.batchActiveAfter);
  EXPECT_FALSE(snapshot.batchFunActiveAfter);
}

}  // namespace test_reaction


