

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <string>
#include <vector>

namespace operator_test_functions {

/**
 * @brief Encapsulates results for type safety related operations.
 */
struct TypeSafetyResult {
    int value_after_plus_equal;
};

/**
 * @brief Executes type-safety-relevant operations on VarExpr and CalcExpr.
 *
 * Note: Operations that should not compile are left commented in tests.
 *
 * @param initial Initial value for VarExpr.
 * @return TypeSafetyResult Recorded value of VarExpr after mutation.
 */
TypeSafetyResult run_type_safety_sequence(int initial) {
    TypeSafetyResult result{};
    auto var_v = reaction::var(initial);
    auto calc_v = reaction::calc([&]() { return var_v() * 2; });

    (void)calc_v; // suppress unused warning

    var_v += 5;
    result.value_after_plus_equal = var_v.get();

    return result;
}

} // namespace operator_test_functions

