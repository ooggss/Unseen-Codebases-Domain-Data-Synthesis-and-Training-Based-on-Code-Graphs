#include <gtest/gtest.h>

#include "test_resource_atomic.hpp"

namespace test_reaction {

/**
 * Test Case: Exercise Resource::atomicOperation to apply an atomic increment.
 */
TEST(reaction, test_resource_atomic) {
  const int initialValue = 15;
  const int delta = 6;

  const auto result = test_resource_atomic(initialValue, delta);

  EXPECT_EQ(result.finalValue, initialValue + delta);
  EXPECT_TRUE(result.operationReportedChange);
}

}  // namespace test_reaction


