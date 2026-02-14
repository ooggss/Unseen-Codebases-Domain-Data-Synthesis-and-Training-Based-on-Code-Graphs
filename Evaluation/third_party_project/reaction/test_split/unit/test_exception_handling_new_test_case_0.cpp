

#include <gtest/gtest.h>
#include <reaction/reaction.h>

// Include function definition (normally via header)
#include "test_exception_handling_function_implementation_0.hpp"

using namespace reaction;

/**
 * @brief Test fixture for exception handling tests.
 */
class ExceptionTest_BasicReactionException : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @brief Test basic ReactionException functionality.
 */
TEST_F(ExceptionTest_BasicReactionException, BasicReactionException) {
    try {
        // ============ Call function that should throw ============
        trigger_basic_reaction_exception("Test message",
                                         ReactionException::ErrorCode::UNKNOWN);

        FAIL() << "Expected ReactionException to be thrown";
    } catch (const ReactionException &e) {
        // ============ Assertions on caught exception ============
        EXPECT_EQ(e.getErrorCode(), ReactionException::ErrorCode::UNKNOWN);
        EXPECT_EQ(e.getOriginalMessage(), "Test message");
        EXPECT_FALSE(e.getFile().empty());
        EXPECT_GT(e.getLine(), 0);
        EXPECT_FALSE(e.getFunction().empty());
    }
}

