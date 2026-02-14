

#include <gtest/gtest.h>
#include <reaction/reaction.h>

#include "test_exception_handling_function_implementation_8.hpp"

using namespace reaction;

class ExceptionTest_BatchOperationConflictException : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @brief Test BatchOperationConflictException.
 */
TEST_F(ExceptionTest_BatchOperationConflictException,
       BatchOperationConflictException) {
    try {
        // ============ Call function that should throw ============
        trigger_batch_operation_conflict_exception("conflicting operations");
        FAIL() << "Expected BatchOperationConflictException to be thrown";
    } catch (const BatchOperationConflictException &e) {
        // ============ Assertions on caught exception ============
        EXPECT_EQ(e.getErrorCode(),
                  ReactionException::ErrorCode::BATCH_OPERATION_CONFLICT);
        EXPECT_EQ(e.getConflictDescription(), "conflicting operations");
    }
}

