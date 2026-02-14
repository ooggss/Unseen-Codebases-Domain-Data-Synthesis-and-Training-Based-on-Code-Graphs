

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <string>
#include <vector>

namespace operator_test_functions {

/**
 * @brief Encapsulates results of floating point operator operations.
 */
struct FloatingPointOperatorsResult {
    double after_plus_equal;
    double after_minus_equal;
    double after_mul_equal;
    double after_div_equal;
    double after_pre_increment;
    double after_post_increment_value;
    double post_increment_old_value;
};

/**
 * @brief Execute floating point operations on a reactive var.
 *
 * @param initial Initial double value.
 * @return FloatingPointOperatorsResult Recorded values after each step.
 */
FloatingPointOperatorsResult run_floating_point_sequence(double initial) {
    FloatingPointOperatorsResult result{};
    auto vf = reaction::var(initial);

    vf += 1.86;
    result.after_plus_equal = vf.get();

    vf -= 1.0;
    result.after_minus_equal = vf.get();

    vf *= 0.5;
    result.after_mul_equal = vf.get();

    vf /= 2.0;
    result.after_div_equal = vf.get();

    ++vf;
    result.after_pre_increment = vf.get();

    auto old_vf = vf++;
    result.after_post_increment_value = vf.get();
    result.post_increment_old_value = old_vf;

    return result;
}

} // namespace operator_test_functions

