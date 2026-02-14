

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <string>
#include <vector>

namespace operator_test_functions {

/**
 * @brief Encapsulates results of compound assignment operations.
 */
struct CompoundAssignmentResult {
    int after_plus_equal;
    int after_minus_equal;
    int after_mul_equal;
    int after_div_equal;
    int after_mod_equal;
};

/**
 * @brief Execute compound assignment operations on a reactive var.
 *
 * @param initial Initial integer value.
 * @return CompoundAssignmentResult Recorded values after each step.
 */
CompoundAssignmentResult run_compound_assignment_sequence(int initial) {
    CompoundAssignmentResult result{};
    auto v = reaction::var(initial);

    v += 5;
    result.after_plus_equal = v.get();

    v -= 3;
    result.after_minus_equal = v.get();

    v *= 2;
    result.after_mul_equal = v.get();

    v /= 4;
    result.after_div_equal = v.get();

    v %= 4;
    result.after_mod_equal = v.get();

    return result;
}

} // namespace operator_test_functions

