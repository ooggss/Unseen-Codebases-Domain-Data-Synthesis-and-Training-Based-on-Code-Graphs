

#include <gtest/gtest.h>
#include <reaction/reaction.h>

#include "test_exception_handling_function_implementation_7.hpp"

using namespace reaction;

class ExceptionTest_ThreadSafetyViolationException : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @brief Test ThreadSafetyViolationException.
 */
TEST_F(ExceptionTest_ThreadSafetyViolationException,
       ThreadSafetyViolationException) {
    try {
        // ============ Call function that should throw ============
        trigger_thread_safety_violation_exception("concurrent access");
        FAIL() << "Expected ThreadSafetyViolationException to be thrown";
    } catch (const ThreadSafetyViolationException &e) {
        // ============ Assertions on caught exception ============
        EXPECT_EQ(e.getErrorCode(),
                  ReactionException::ErrorCode::THREAD_SAFETY_VIOLATION);
        EXPECT_EQ(e.getOperation(), "concurrent access");
    }
}

