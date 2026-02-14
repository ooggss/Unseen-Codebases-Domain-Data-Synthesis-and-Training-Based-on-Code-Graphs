#include <gtest/gtest.h>

#include "test_sbo_storage_info.hpp"

namespace test_reaction {

/**
 * Test Case: Verify SBOResource chooses stack storage for small payloads and heap for large payloads.
 *
 * Test Scenario:
 * - Construct SBO resources for a small and a large payload type
 * - Update the small resource to exercise updateValue and ensure the change is detected
 * - Check StorageInfo to confirm stack usage is reported only for the small payload
 */
TEST(reaction, test_sbo_storage_info) {
  const auto status = test_sbo_storage_info(5, 17, 3);

  EXPECT_TRUE(status.updateReportedChange);
  EXPECT_TRUE(status.smallUsingSBO);
  EXPECT_EQ(status.smallStackUsage, sizeof(SmallPayload));
  EXPECT_TRUE(status.largeInitialized);
  EXPECT_FALSE(status.largeUsingSBO);
}

}  // namespace test_reaction

