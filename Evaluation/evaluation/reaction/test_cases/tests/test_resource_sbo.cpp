#include <gtest/gtest.h>

#include "test_resource_sbo.hpp"

namespace test_reaction {

/**
 * Test Case: Verify Resource enables SBO for small types but not large ones
 *
 * Test Scenario:
 * - Instantiate Resource<int> and Resource<std::array<int,256>>
 * - Query isUsingSBO() on both instances
 * - Ensure only the small type reports SBO usage
 */
TEST(reaction, test_resource_sbo) {
  const auto state = test_resource_sbo();

  EXPECT_TRUE(state.smallTypeUsesSBO);
  EXPECT_FALSE(state.largeTypeUsesSBO);
}

}  // namespace test_reaction


