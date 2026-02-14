

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "test_expression_division_function_implementation_6.hpp"

using namespace reaction;

namespace expression_division_tests {

TEST(ExpressionDivisionTest, TestDivisionInBatchOperations) {
    // ============ Construct Function Inputs & Call Function ============
    auto [numerator, denominator, result] =
        expression_division_impl::create_division_batch_operation_expression();

    int triggerCount = 0;
    auto observer = action(
        [&](double value) {
            triggerCount++;
            EXPECT_DOUBLE_EQ(value, 3.75); // 15/4 = 3.75
        },
        result);

    (void)observer; // prevent unused variable warning

    triggerCount = 0;

    // ============ Perform Batch Operation ============
    batchExecute([&]() {
        numerator.value(15);
        denominator.value(4);
    });

    // ============ Assert to Verify Behavior ============
    EXPECT_EQ(triggerCount, 1); // Should trigger only once
    EXPECT_DOUBLE_EQ(result.get(), 3.75);
}

}  // namespace expression_division_tests

