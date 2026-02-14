

#include <gtest/gtest.h>
#include <reaction/reaction.h>

#include "test_exception_handling_function_implementation_3.hpp"

using namespace reaction;

class ExceptionTest_NullPointerAccessException : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @brief Test NullPointerAccessException.
 */
TEST_F(ExceptionTest_NullPointerAccessException, NullPointerAccessException) {
    try {
        // ============ Call function that should throw ============
        trigger_null_pointer_access_exception("weak pointer access");
        FAIL() << "Expected NullPointerAccessException to be thrown";
    } catch (const NullPointerAccessException &e) {
        // ============ Assertions on caught exception ============
        EXPECT_EQ(e.getErrorCode(), ReactionException::ErrorCode::NULL_POINTER_ACCESS);
        EXPECT_EQ(e.getContext(), "weak pointer access");
        EXPECT_TRUE(std::string(e.what()).find("weak pointer access") != std::string::npos);
    }
}

