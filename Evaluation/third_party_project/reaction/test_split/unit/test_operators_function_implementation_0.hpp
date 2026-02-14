

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <string>
#include <vector>

namespace operator_test_functions {

/**
 * @brief Encapsulates results of increment/decrement operator operations.
 */
struct IncrementDecrementResult {
    int initial_value;
    int after_pre_increment;
    int value_after_post_increment;
    int post_increment_old_value;
    int after_pre_decrement;
    int value_after_post_decrement;
    int post_decrement_old_value;
};

/**
 * @brief Execute a sequence of increment/decrement operations on a reactive var.
 *
 * @param initial Initial value for the reactive variable.
 * @return IncrementDecrementResult Captured values through the operation sequence.
 */
IncrementDecrementResult run_increment_decrement_sequence(int initial) {
    IncrementDecrementResult result{};
    auto v1 = reaction::var(initial);

    result.initial_value = v1.get();

    ++v1;
    result.after_pre_increment = v1.get();

    auto old_val = v1++;
    result.value_after_post_increment = v1.get();
    result.post_increment_old_value = old_val;

    --v1;
    result.after_pre_decrement = v1.get();

    auto old_val2 = v1--;
    result.value_after_post_decrement = v1.get();
    result.post_decrement_old_value = old_val2;

    return result;
}

} // namespace operator_test_functions

