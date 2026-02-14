#include <gtest/gtest.h>

#include "test_graph_reset_node.hpp"

namespace test_reaction {

/**
 * Test Case: Ensure ObserverGraph::resetNode removes dependencies.
 *
 * Test Scenario:
 * - Create a source and target ResetAwareNode
 * - Add observer relationship, fire notification (target should receive)
 * - Call resetNode(target) and fire again (target should not receive)
 */
TEST(reaction, test_graph_reset_node) {
  const auto result = test_graph_reset_node("source", "target");

  EXPECT_TRUE(result.notifiedBeforeReset);
  EXPECT_FALSE(result.notifiedAfterReset);
}

}  // namespace test_reaction

