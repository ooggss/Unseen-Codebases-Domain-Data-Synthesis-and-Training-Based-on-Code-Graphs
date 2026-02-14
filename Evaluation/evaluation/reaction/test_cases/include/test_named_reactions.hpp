#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

// ============================================
// Function implementations
// ============================================

/**
 * Function: Test naming reactive nodes and retrieving names
 *
 * @param valueA Initial value for varA
 * @param valueB Initial value for varB
 * @return std::string Combined string of retrieved names
 */
std::string test_named_reactions(int valueA, int valueB) {
    using namespace reaction;

    // Create reactive variables and calculations
    auto varA = var(valueA).setName("input_a");
    auto varB = var(valueB).setName("input_b");

    auto sumCalc = calc([](int a, int b) {
        return a + b;
    }, varA, varB).setName("sum_calc");

    auto doubleCalc = calc([](int sum) {
        return sum * 2;
    }, sumCalc).setName("double_calc");

    auto logger = action([](int doubled) {
        (void)doubled;
    }, doubleCalc).setName("logger_action");

    // Retrieve names via getName() to verify naming functionality
    const std::string names =
        varA.getName() + "|" + varB.getName() + "|" + sumCalc.getName() + "|" +
        doubleCalc.getName() + "|" + logger.getName();

    return names;
}

}  // namespace test_reaction

