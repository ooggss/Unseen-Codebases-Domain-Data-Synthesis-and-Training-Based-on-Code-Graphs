

#include <gtest/gtest.h>
#include <reaction/reaction.h>

#include "test_exception_handling_function_implementation_11.hpp"

using namespace reaction;

class ExceptionTest_RealNullPointerAccess : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @brief Test actual null pointer access with new exceptions.
 */
TEST_F(ExceptionTest_RealNullPointerAccess, RealNullPointerAccess) {
    // ============ Call function ============
    bool thrown = access_closed_variable_throws_null_pointer();

    // ============ Assertions ============
    EXPECT_TRUE(thrown);
}

