

#include <gtest/gtest.h>
#include <reaction/reaction.h>

#include "test_exception_handling_function_implementation_1.hpp"

using namespace reaction;

class ExceptionTest_DependencyCycleException : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @brief Test DependencyCycleException.
 */
TEST_F(ExceptionTest_DependencyCycleException, DependencyCycleException) {
    try {
        // ============ Call function that should throw ============
        trigger_dependency_cycle_exception("NodeA", "NodeB");
        FAIL() << "Expected DependencyCycleException to be thrown";
    } catch (const DependencyCycleException &e) {
        // ============ Assertions on caught exception ============
        EXPECT_EQ(e.getErrorCode(), ReactionException::ErrorCode::DEPENDENCY_CYCLE);
        EXPECT_EQ(e.getSourceName(), "NodeA");
        EXPECT_EQ(e.getTargetName(), "NodeB");
        EXPECT_NE(e.what(), nullptr);
        EXPECT_TRUE(std::string(e.what()).find("NodeA") != std::string::npos);
        EXPECT_TRUE(std::string(e.what()).find("NodeB") != std::string::npos);
    }
}

