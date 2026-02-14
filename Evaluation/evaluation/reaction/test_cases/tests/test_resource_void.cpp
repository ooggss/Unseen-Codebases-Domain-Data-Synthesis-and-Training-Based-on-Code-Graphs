#include <gtest/gtest.h>

#include "test_resource_void.hpp"

namespace test_reaction {

/**
 * Test Case: Validate Resource<Void> SBO usage and graph naming lifecycle.
 *
 * Test Scenario:
 * - Create a shared Resource<Void> node and verify SBO is always active
 * - Register it with ObserverGraph, assign a name, and ensure retrieval works
 * - Close the node and confirm that the name mapping disappears
 */
TEST(reaction, test_resource_void_behavior) {
  const auto snapshot = test_resource_void_behavior("void-node");

  EXPECT_TRUE(snapshot.retrievedIsVoid);
  EXPECT_TRUE(snapshot.usesSboStorage);
  EXPECT_TRUE(snapshot.nameAssigned);
  EXPECT_TRUE(snapshot.nameClearedAfterClose);
}

}  // namespace test_reaction

