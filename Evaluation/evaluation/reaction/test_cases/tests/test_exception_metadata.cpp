#include <gtest/gtest.h>

#include "test_exception_metadata.hpp"

namespace test_reaction {

/**
 * Test Case: Validate ReactionException metadata accessors.
 *
 * Test Scenario:
 * - Create a ReactionException with explicit metadata
 * - Ensure getters expose original message, file, line, function, and code string
 */
TEST(reaction, test_exception_metadata) {
  const std::string message = "Critical failure";
  const std::string file = "engine/core.cpp";
  const std::string function = "performWork";
  const int line = 77;

  const auto info = capture_exception_info(
      message,
      reaction::ReactionException::ErrorCode::INVALID_STATE,
      file,
      line,
      function);

  EXPECT_EQ(info.originalMessage, message);
  EXPECT_EQ(info.file, file);
  EXPECT_EQ(info.line, line);
  EXPECT_EQ(info.function, function);
  EXPECT_EQ(info.codeName, "INVALID_STATE");
  EXPECT_NE(info.formattedMessage.find(file), std::string::npos);
  EXPECT_NE(info.formattedMessage.find("INVALID_STATE"), std::string::npos);
}

}  // namespace test_reaction

