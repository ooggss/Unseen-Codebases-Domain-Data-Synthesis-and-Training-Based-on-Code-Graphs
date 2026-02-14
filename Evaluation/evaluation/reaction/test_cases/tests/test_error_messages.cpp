#include <gtest/gtest.h>

#include "test_error_messages.hpp"

namespace test_reaction {

/**
 * Test Case: Verify ReactionException::errorCodeToString mapping.
 *
 * Test Scenario:
 * - Provide multiple error codes (dependency cycle, null pointer, graph corruption)
 * - Ensure returned strings match enum names
 */
TEST(reaction, test_error_messages) {
  const std::vector<reaction::ReactionException::ErrorCode> codes = {
      reaction::ReactionException::ErrorCode::DEPENDENCY_CYCLE,
      reaction::ReactionException::ErrorCode::NULL_POINTER_ACCESS,
      reaction::ReactionException::ErrorCode::GRAPH_CORRUPTION,
  };

  const auto descriptions = describe_error_codes(codes);

  ASSERT_EQ(descriptions.size(), 3u);
  EXPECT_EQ(descriptions[0], "DEPENDENCY_CYCLE");
  EXPECT_EQ(descriptions[1], "NULL_POINTER_ACCESS");
  EXPECT_EQ(descriptions[2], "GRAPH_CORRUPTION");
}

}  // namespace test_reaction

