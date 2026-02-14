

#include <gtest/gtest.h>
#include <reaction/reaction.h>

#include "test_exception_handling_function_implementation_6.hpp"

using namespace reaction;

class ExceptionTest_InvalidStateException : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @brief Test InvalidStateException.
 */
TEST_F(ExceptionTest_InvalidStateException, InvalidStateException) {
    try {
        // ============ Call function that should throw ============
        trigger_invalid_state_exception("current", "required");
        FAIL() << "Expected InvalidStateException to be thrown";
    } catch (const InvalidStateException &e) {
        // ============ Assertions on caught exception ============
        EXPECT_EQ(e.getErrorCode(), ReactionException::ErrorCode::INVALID_STATE);
        EXPECT_EQ(e.getCurrentState(), "current");
        EXPECT_EQ(e.getRequiredState(), "required");
    }
}

