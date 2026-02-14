

#include <gtest/gtest.h>
#include <reaction/reaction.h>

#include "test_exception_handling_function_implementation_2.hpp"

using namespace reaction;

class ExceptionTest_SelfObservationException : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @brief Test SelfObservationException.
 */
TEST_F(ExceptionTest_SelfObservationException, SelfObservationException) {
    try {
        // ============ Call function that should throw ============
        trigger_self_observation_exception("SelfNode");
        FAIL() << "Expected SelfObservationException to be thrown";
    } catch (const SelfObservationException &e) {
        // ============ Assertions on caught exception ============
        EXPECT_EQ(e.getErrorCode(), ReactionException::ErrorCode::SELF_OBSERVATION);
        EXPECT_EQ(e.getNodeName(), "SelfNode");
        EXPECT_TRUE(std::string(e.what()).find("SelfNode") != std::string::npos);
    }
}

