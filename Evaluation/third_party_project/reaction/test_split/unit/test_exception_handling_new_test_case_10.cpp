

#include <gtest/gtest.h>
#include <reaction/reaction.h>

#include "test_exception_handling_function_implementation_10.hpp"

using namespace reaction;

class ExceptionTest_RealDependencyCycleDetection : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @brief Test actual dependency cycle detection with new exceptions.
 */
TEST_F(ExceptionTest_RealDependencyCycleDetection,
       RealDependencyCycleDetection) {
    // ============ Call function ============
    std::string result = perform_real_dependency_cycle_detection();

    // ============ Assertions ============
    // The original test accepts multiple possible exception types,
    // only failing on "unknown". Here we replicate that behavior.
    EXPECT_NE(result, "unknown");
}

