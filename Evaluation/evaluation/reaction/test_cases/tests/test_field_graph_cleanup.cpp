#include <gtest/gtest.h>

#include "test_field_graph_cleanup.hpp"

namespace test_reaction {

/**
 * Test Case: Ensure FieldGraph::deleteObj prevents future bindings.
 *
 * Test Scenario:
 * - Register a field node under an object ID and bind it to an owner
 * - After verifying notifications, reset the owner and delete the object entry
 * - Attempt to bind again; field notifications should no longer reach the owner
 */
TEST(reaction, test_field_graph_cleanup) {
  constexpr uint64_t objectId = 42;

  const auto result = test_field_graph_cleanup(objectId);

  EXPECT_TRUE(result.notifiedBeforeDelete);
  EXPECT_FALSE(result.notifiedAfterDelete);
}

}  // namespace test_reaction

