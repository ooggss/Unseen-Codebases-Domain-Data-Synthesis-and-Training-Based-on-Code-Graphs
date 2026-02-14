

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Function implementation extracted from:
// TEST(BatchOperationsTest, TestComplexDependenciesWithMultipleAssignments)
namespace batch_operations_impl {

struct ComplexMultipleAssignmentsResult {
    // After first batch
    int triggerCountA1;
    int triggerCountB1;
    int triggerCountC1;
    int triggerCountSum1;
    int triggerCountProduct1;
    int triggerCountCombined1;
    int triggerCountFinal1;
    int A1;
    int B1;
    int C1;
    int Sum1;
    int Product1;
    int Combined1;
    int Final1;

    // After second batch (only d changes)
    int triggerCountA2;
    int triggerCountB2;
    int triggerCountC2;
    int triggerCountSum2;
    int triggerCountProduct2;
    int triggerCountCombined2;
    int triggerCountFinal2;
    int C2;
    int Sum2;
    int Combined2;
    int Final2;
};

/**
 * Complex dependency scenario with multiple assignments in a single batch
 * and a follow-up batch that touches only one variable.
 *
 * @return ComplexMultipleAssignmentsResult capturing trigger counts and values.
 */
ComplexMultipleAssignmentsResult runComplexDependenciesWithMultipleAssignments() {
    // Create base variables
    auto a = reaction::var(1).setName("a");
    auto b = reaction::var(2).setName("b");
    auto c = reaction::var(3).setName("c");
    auto d = reaction::var(4).setName("d");

    // Track trigger counts for all computed values
    int triggerCountA = 0, triggerCountB = 0, triggerCountC = 0;
    int triggerCountSum = 0, triggerCountProduct = 0, triggerCountCombined = 0;
    int triggerCountFinal = 0;

    // Create computed values with complex dependencies
    auto A = reaction::calc([&]() {
        triggerCountA++;
        return a() + b();
    }).setName("A");

    auto B = reaction::calc([&]() {
        triggerCountB++;
        return b() * c();
    }).setName("B");

    auto C = reaction::calc([&]() {
        triggerCountC++;
        return c() + d();
    }).setName("C");

    auto Sum = reaction::calc([&]() {
        triggerCountSum++;
        return A() + B() + C();
    }).setName("Sum");

    auto Product = reaction::calc([&]() {
        triggerCountProduct++;
        return A() * B();
    }).setName("Product");

    auto Combined = reaction::calc([&]() {
        triggerCountCombined++;
        return Sum() - Product();
    }).setName("Combined");

    auto Final = reaction::calc([&]() {
        triggerCountFinal++;
        return Combined() * C();
    }).setName("Final");

    // Precompute initial values (ensures calc nodes are created)
    (void)A.get();
    (void)B.get();
    (void)C.get();
    (void)Sum.get();
    (void)Product.get();
    (void)Combined.get();
    (void)Final.get();

    // Reset counters
    triggerCountA = triggerCountB = triggerCountC = 0;
    triggerCountSum = triggerCountProduct = triggerCountCombined = 0;
    triggerCountFinal = 0;

    // Execute batch with multiple assignments
    reaction::batchExecute([&]() {
        a.value(10);
        b.value(20);
        c.value(30);
        d.value(40);
    });

    ComplexMultipleAssignmentsResult result{};

    // After first batch
    result.triggerCountA1 = triggerCountA;
    result.triggerCountB1 = triggerCountB;
    result.triggerCountC1 = triggerCountC;
    result.triggerCountSum1 = triggerCountSum;
    result.triggerCountProduct1 = triggerCountProduct;
    result.triggerCountCombined1 = triggerCountCombined;
    result.triggerCountFinal1 = triggerCountFinal;

    result.A1 = A.get();
    result.B1 = B.get();
    result.C1 = C.get();
    result.Sum1 = Sum.get();
    result.Product1 = Product.get();
    result.Combined1 = Combined.get();
    result.Final1 = Final.get();

    // Additional test: updating only one variable
    triggerCountA = triggerCountB = triggerCountC = 0;
    triggerCountSum = triggerCountProduct = triggerCountCombined = 0;
    triggerCountFinal = 0;

    reaction::batchExecute([&]() {
        d.value(50);
    });

    result.triggerCountA2 = triggerCountA;
    result.triggerCountB2 = triggerCountB;
    result.triggerCountC2 = triggerCountC;
    result.triggerCountSum2 = triggerCountSum;
    result.triggerCountProduct2 = triggerCountProduct;
    result.triggerCountCombined2 = triggerCountCombined;
    result.triggerCountFinal2 = triggerCountFinal;

    result.C2 = C.get();
    result.Sum2 = Sum.get();
    result.Combined2 = Combined.get();
    result.Final2 = Final.get();

    return result;
}

} // namespace batch_operations_impl

