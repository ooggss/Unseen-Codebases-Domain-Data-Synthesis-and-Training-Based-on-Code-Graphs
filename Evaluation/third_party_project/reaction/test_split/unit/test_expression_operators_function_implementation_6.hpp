

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

namespace expression_operators_impl {

using namespace reaction;

/**
 * Execute batch-operation-related expressions and return their evaluated
 * results, including observer trigger count and final expression value.
 */
struct BatchOperatorsResult {
    int triggerCount;
    bool result_value;
};

BatchOperatorsResult run_operators_batch_scenario() {
    auto x = var(10).setName("x");
    auto y = var(5).setName("y");
    auto result = expr((x > y) && (x / y == 2)).setName("result");

    int triggerCount = 0;
    auto observer = action([&](bool value) {
                              triggerCount++;
                              // In the original test, the expectation is that
                              // the value is true both initially and after update.
                              (void)value;
                          },
                          result);

    triggerCount = 0;

    // Test batch execution with operators
    batchExecute([&]() {
        x.value(20);
        y.value(10);
    });

    BatchOperatorsResult r{
        .triggerCount = triggerCount,
        .result_value = result.get() // (20>10) && (20/10==2) is true
    };

    return r;
}

} // namespace expression_operators_impl

