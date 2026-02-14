

#include <gtest/gtest.h>
#include <reaction/reaction.h>

#include "test_exception_handling_function_implementation_5.hpp"

using namespace reaction;

class ExceptionTest_TypeMismatchException : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @brief Test TypeMismatchException.
 */
TEST_F(ExceptionTest_TypeMismatchException, TypeMismatchException) {
    try {
        // ============ Call function that should throw ============
        trigger_type_mismatch_exception("int", "double");
        FAIL() << "Expected TypeMismatchException to be thrown";
    } catch (const TypeMismatchException &e) {
        // ============ Assertions on caught exception ============
        EXPECT_EQ(e.getErrorCode(), ReactionException::ErrorCode::TYPE_MISMATCH);
        EXPECT_EQ(e.getExpectedType(), "int");
        EXPECT_EQ(e.getActualType(), "double");
        EXPECT_TRUE(std::string(e.what()).find("int") != std::string::npos);
        EXPECT_TRUE(std::string(e.what()).find("double") != std::string::npos);
    }
}

