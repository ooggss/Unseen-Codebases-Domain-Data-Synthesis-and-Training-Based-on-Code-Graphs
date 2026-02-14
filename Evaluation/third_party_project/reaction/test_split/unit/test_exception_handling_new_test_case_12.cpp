

#include <gtest/gtest.h>
#include <reaction/reaction.h>

#include "test_exception_handling_function_implementation_12.hpp"

using namespace reaction;

class ExceptionTest_RealTypeMismatch : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @brief Test type mismatch in expression reset.
 */
TEST_F(ExceptionTest_RealTypeMismatch, RealTypeMismatch) {
    // ============ Call function ============
    std::string result = perform_real_type_mismatch_reset();

    // ============ Assertions ============
    // Original test allows both success and several exception types,
    // and only fails on completely unknown type.
    EXPECT_NE(result, "unknown");
}

