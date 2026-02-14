

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <stdexcept>

// Function implementation extracted from:
// TEST(BatchOperationsTest, TestComplexDependencyBatchResetProtection)
namespace batch_operations_impl {

struct ComplexBatchResetProtectionResult {
    // Initial values
    int calc1_initial;
    int calc2_initial;
    int calc3_initial;
    int calc4_initial;
    int calc5_initial;
    int calc6_initial;
    int calc7_initial;
    int calc8_initial;
    int calc9_initial;
    int calc10_initial;

    // After batch is created but before execution
    bool resetsThrowWhileActive;
    int calc1_before_execute;
    int calc2_before_execute;
    int calc3_before_execute;

    // After batch execute
    int var1_after;
    int var2_after;
    int var3_after;
    int var4_after;

    int calc1_after;
    int calc2_after;
    int calc3_after;
    int calc4_after;
    int calc5_after;
    int calc6_after;
    int calc7_after;
    int calc8_after;
    int calc9_after;
    int calc10_after;

    bool resetStillThrowsAfterExecute;

    // After batch close and subsequent resets
    int calc1_after_reset;
    int calc2_after_reset;
    int calc3_after_reset;
    int calc5_after_reset;
    bool batch_is_closed;
};

/**
 * Complex dependency graph with batch reset protection.
 *
 * @return ComplexBatchResetProtectionResult capturing values and reset behavior.
 */
ComplexBatchResetProtectionResult runComplexDependencyBatchResetProtectionScenario() {
    ComplexBatchResetProtectionResult result{};

    auto var1 = reaction::var(1).setName("var1");
    auto var2 = reaction::var(2).setName("var2");
    auto var3 = reaction::var(3).setName("var3");
    auto var4 = reaction::var(4).setName("var4");

    auto calc1 = reaction::calc([&]() { return var1() + var2(); }).setName("calc1");
    auto calc2 = reaction::calc([&]() { return calc1() * 2; }).setName("calc2");
    auto calc3 = reaction::calc([&]() { return calc2() + 1; }).setName("calc3");

    auto calc4 = reaction::calc([&]() { return var2() + var3(); }).setName("calc4");
    auto calc5 = reaction::calc([&]() { return calc4() * 3; }).setName("calc5");

    auto calc6 = reaction::calc([&]() { return var3() + var4(); }).setName("calc6");
    auto calc7 = reaction::calc([&]() { return calc6() * 4; }).setName("calc7");

    auto calc8 = reaction::calc([&]() { return var4() * 2; }).setName("calc8");
    auto calc9 = reaction::calc([&]() { return calc8() + 5; }).setName("calc9");
    auto calc10 = reaction::calc([&]() { return calc9() * 2; }).setName("calc10");

    // Initial values check
    result.calc1_initial = calc1.get();
    result.calc2_initial = calc2.get();
    result.calc3_initial = calc3.get();
    result.calc4_initial = calc4.get();
    result.calc5_initial = calc5.get();
    result.calc6_initial = calc6.get();
    result.calc7_initial = calc7.get();
    result.calc8_initial = calc8.get();
    result.calc9_initial = calc9.get();
    result.calc10_initial = calc10.get();

    // Create a batch that affects multiple parts of the dependency graph
    auto batch = reaction::batch([&]() {
        var1.value(10);
        var2.value(20);
        var3.value(30);
        var4.value(40);
    });

    // While batch is active, all reset operations should be prevented
    bool allThrow = true;
    try { calc1.reset([&]() { return var1() * 2; }); allThrow = false; } catch (...) {}
    try { calc2.reset([&]() { return calc1() + 10; }); allThrow = false; } catch (...) {}
    try { calc3.reset([&]() { return calc2() * 2; }); allThrow = false; } catch (...) {}
    try { calc4.reset([&]() { return var2() + var3(); }); allThrow = false; } catch (...) {}
    try { calc5.reset([&]() { return calc4() * 5; }); allThrow = false; } catch (...) {}
    try { calc6.reset([&]() { return var3() * var4(); }); allThrow = false; } catch (...) {}
    try { calc7.reset([&]() { return calc6() + 100; }); allThrow = false; } catch (...) {}
    try { calc8.reset([&]() { return var4() + 10; }); allThrow = false; } catch (...) {}
    try { calc9.reset([&]() { return calc8() * 3; }); allThrow = false; } catch (...) {}
    try { calc10.reset([&]() { return calc9() + 50; }); allThrow = false; } catch (...) {}
    result.resetsThrowWhileActive = allThrow;

    // Verify values haven't changed before execute
    result.calc1_before_execute = calc1.get();
    result.calc2_before_execute = calc2.get();
    result.calc3_before_execute = calc3.get();

    // Execute the batch
    batch.execute();

    // Now values should be updated
    result.var1_after = var1.get();
    result.var2_after = var2.get();
    result.var3_after = var3.get();
    result.var4_after = var4.get();

    result.calc1_after = calc1.get();
    result.calc2_after = calc2.get();
    result.calc3_after = calc3.get();
    result.calc4_after = calc4.get();
    result.calc5_after = calc5.get();
    result.calc6_after = calc6.get();
    result.calc7_after = calc7.get();
    result.calc8_after = calc8.get();
    result.calc9_after = calc9.get();
    result.calc10_after = calc10.get();

    // After batch execution, it's still active, so reset should still be prevented
    bool stillThrows = false;
    try {
        calc1.reset([&]() { return var1() * 2; });
    } catch (...) {
        stillThrows = true;
    }
    result.resetStillThrowsAfterExecute = stillThrows;

    // Manually close the batch
    batch.close();

    // Now reset operations should work
    calc1.reset([&]() { return var1() * 2; });
    result.calc1_after_reset = calc1.get();

    // Propagate through the dependency chain
    result.calc2_after_reset = calc2.get();
    result.calc3_after_reset = calc3.get();

    // Other nodes can also be reset
    calc5.reset([&]() { return calc4() + 1000; });
    result.calc5_after_reset = calc5.get();

    result.batch_is_closed = batch.isClosed();

    return result;
}

} // namespace batch_operations_impl

