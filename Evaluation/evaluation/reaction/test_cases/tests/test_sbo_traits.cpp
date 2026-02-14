#include <gtest/gtest.h>

#include "test_sbo_traits.hpp"

namespace test_reaction {

/**
 * Test Case: Verify SBOTraits and SBOConfig thresholds for different payload sizes.
 *
 * Test Scenario:
 * - Inspect compile-time SBOTraits flags for tiny/medium/large POD types
 * - Ensure thresholds reported by SBOConfig match expected constants
 */
TEST(reaction, test_sbo_traits) {
  const auto summary = analyze_sbo_traits();

  EXPECT_TRUE(summary.tinyAlwaysSbo);
  EXPECT_FALSE(summary.tinyForceHeap);
  EXPECT_TRUE(summary.mediumConditionalSbo);
  EXPECT_FALSE(summary.mediumForceHeap);
  EXPECT_TRUE(summary.largeForceHeap);
  EXPECT_EQ(summary.alwaysThreshold, 16u);
  EXPECT_EQ(summary.conditionalThreshold, 32u);
  EXPECT_EQ(summary.maxStackUsage, 64u * 1024u);
}

}  // namespace test_reaction

