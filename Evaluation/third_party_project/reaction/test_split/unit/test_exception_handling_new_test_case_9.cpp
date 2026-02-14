

#include <gtest/gtest.h>
#include <reaction/reaction.h>
#include <vector>
#include <string>

#include "test_exception_handling_function_implementation_9.hpp"

using namespace reaction;

class ExceptionTest_ErrorCodeToString : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @brief Test error code to string conversion.
 */
TEST_F(ExceptionTest_ErrorCodeToString, ErrorCodeToString) {
    // ============ Construct function input ============
    std::vector<ReactionException::ErrorCode> codes = {
        ReactionException::ErrorCode::DEPENDENCY_CYCLE,
        ReactionException::ErrorCode::SELF_OBSERVATION,
        ReactionException::ErrorCode::NULL_POINTER_ACCESS,
        ReactionException::ErrorCode::RESOURCE_NOT_INITIALIZED,
        ReactionException::ErrorCode::TYPE_MISMATCH,
        ReactionException::ErrorCode::INVALID_STATE,
        ReactionException::ErrorCode::THREAD_SAFETY_VIOLATION,
        ReactionException::ErrorCode::BATCH_OPERATION_CONFLICT,
        ReactionException::ErrorCode::UNKNOWN};

    // ============ Call function ============
    auto strings = convert_error_codes_to_strings(codes);

    // ============ Assertions ============
    ASSERT_EQ(strings.size(), codes.size());
    EXPECT_EQ(strings[0], "DEPENDENCY_CYCLE");
    EXPECT_EQ(strings[1], "SELF_OBSERVATION");
    EXPECT_EQ(strings[2], "NULL_POINTER_ACCESS");
    EXPECT_EQ(strings[3], "RESOURCE_NOT_INITIALIZED");
    EXPECT_EQ(strings[4], "TYPE_MISMATCH");
    EXPECT_EQ(strings[5], "INVALID_STATE");
    EXPECT_EQ(strings[6], "THREAD_SAFETY_VIOLATION");
    EXPECT_EQ(strings[7], "BATCH_OPERATION_CONFLICT");
    EXPECT_EQ(strings[8], "UNKNOWN");
}

