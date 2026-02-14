

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <string>
#include <vector>

namespace operator_test_functions {

/**
 * @brief Encapsulates results for mixed numeric type operations.
 */
struct MixedNumericTypesResult {
    int int_after_plus_equal_double;
    double double_after_plus_equal_int;
    double double_after_mul_equal_int;
};

/**
 * @brief Execute mixed numeric type operations on reactive vars.
 *
 * @param int_initial Initial integer value.
 * @param double_initial Initial double value.
 * @return MixedNumericTypesResult Recorded values after operations.
 */
MixedNumericTypesResult run_mixed_numeric_types_sequence(int int_initial, double double_initial) {
    MixedNumericTypesResult result{};
    auto v_int = reaction::var(int_initial);
    auto v_double = reaction::var(double_initial);

    v_int += 2.5;
    result.int_after_plus_equal_double = v_int.get();

    v_double += 1;
    result.double_after_plus_equal_int = v_double.get();

    v_double *= 2;
    result.double_after_mul_equal_int = v_double.get();

    return result;
}

} // namespace operator_test_functions

