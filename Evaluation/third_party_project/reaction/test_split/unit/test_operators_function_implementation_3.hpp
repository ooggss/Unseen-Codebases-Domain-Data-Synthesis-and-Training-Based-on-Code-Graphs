

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <string>
#include <vector>

namespace operator_test_functions {

/**
 * @brief Encapsulates results of bitwise operator operations.
 */
struct BitwiseOperatorsResult {
    int after_and_equal;
    int after_or_equal;
    int after_xor_equal;
    int after_shift_left_equal;
    int after_shift_right_equal;
};

/**
 * @brief Execute bitwise operations on a reactive var.
 *
 * @param initial Initial integer value (bit pattern).
 * @return BitwiseOperatorsResult Recorded values after each step.
 */
BitwiseOperatorsResult run_bitwise_sequence(int initial) {
    BitwiseOperatorsResult result{};
    auto v = reaction::var(initial);

    v &= 0b1100;
    result.after_and_equal = v.get();

    v.value(initial);
    v |= 0b0101;
    result.after_or_equal = v.get();

    v.value(initial);
    v ^= 0b0110;
    result.after_xor_equal = v.get();

    v <<= 1;
    result.after_shift_left_equal = v.get();

    v >>= 2;
    result.after_shift_right_equal = v.get();

    return result;
}

} // namespace operator_test_functions

