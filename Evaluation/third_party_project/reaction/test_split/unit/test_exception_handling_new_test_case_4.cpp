

#include <gtest/gtest.h>
#include <reaction/reaction.h>

#include "test_exception_handling_function_implementation_4.hpp"

using namespace reaction;

class ExceptionTest_ResourceNotInitializedException : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @brief Test ResourceNotInitializedException.
 */
TEST_F(ExceptionTest_ResourceNotInitializedException,
       ResourceNotInitializedException) {
    try {
        // ============ Call function that should throw ============
        trigger_resource_not_initialized_exception("TestResource");
        FAIL() << "Expected ResourceNotInitializedException to be thrown";
    } catch (const ResourceNotInitializedException &e) {
        // ============ Assertions on caught exception ============
        EXPECT_EQ(e.getErrorCode(),
                  ReactionException::ErrorCode::RESOURCE_NOT_INITIALIZED);
        EXPECT_EQ(e.getResourceType(), "TestResource");
        EXPECT_TRUE(std::string(e.what()).find("TestResource") != std::string::npos);
    }
}

