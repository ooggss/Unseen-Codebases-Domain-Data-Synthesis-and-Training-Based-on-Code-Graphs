

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <stdexcept>
#include <iostream>

// Function implementation extracted from:
// TEST(BatchOperationsTest, TestBatchResetProtection)
namespace batch_operations_impl {

struct BatchResetProtectionResult {
    bool exceptionThrown;
    int var1_value;
    int calc1_value;
};

/**
 * Test batch reset protection:
 * - Create batch with var1 update
 * - Attempt to reset calc1 while batch is active
 *
 * @return BatchResetProtectionResult with whether exception was thrown and node values.
 */
BatchResetProtectionResult runBatchResetProtectionScenario() {
    auto var1 = reaction::var(5).setName("var1");
    auto calc1 = reaction::calc([&]() { return var1() * 2; }).setName("calc1");

    // Create a batch that keeps the nodes active
    std::cout << "Creating batch..." << std::endl;
    auto batch = reaction::batch([&]() {
        var1.value(10);
    });

    std::cout << "Batch created." << std::endl;

    bool exceptionThrown = false;
    try {
        calc1.reset([&]() { return var1() + 100; });
        std::cout << "Reset succeeded (unexpected)" << std::endl;
    } catch (const std::runtime_error &e) {
        std::cout << "Reset threw exception as expected: " << e.what() << std::endl;
        exceptionThrown = true;
    }

    BatchResetProtectionResult result{
        .exceptionThrown = exceptionThrown,
        .var1_value = var1.get(),
        .calc1_value = calc1.get(),
    };
    return result;
}

} // namespace batch_operations_impl

