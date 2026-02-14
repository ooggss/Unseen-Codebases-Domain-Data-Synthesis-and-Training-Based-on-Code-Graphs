

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <string>
#include <vector>

namespace operator_test_functions {

/**
 * @brief Encapsulates results for edge case and boundary condition operations.
 */
struct EdgeCasesResult {
    int zero_after_pre_increment;
    int zero_after_pre_decrement;
    int neg_after_plus_equal;
    int neg_after_mul_equal;
    int post_inc_old1;
    int post_dec_old2;
    int final_v_test_value;
};

/**
 * @brief Execute a sequence of edge-case operations.
 *
 * @param zero_initial Initial value for zero-var.
 * @param neg_initial Initial negative value.
 * @param test_initial Initial value for post-inc/dec test.
 * @return EdgeCasesResult Recorded values after operations.
 */
EdgeCasesResult run_edge_cases_sequence(int zero_initial, int neg_initial, int test_initial) {
    EdgeCasesResult result{};

    auto v_zero = reaction::var(zero_initial);
    ++v_zero;
    result.zero_after_pre_increment = v_zero.get();

    --v_zero;
    result.zero_after_pre_decrement = v_zero.get();

    auto v_neg = reaction::var(neg_initial);
    v_neg += 10;
    result.neg_after_plus_equal = v_neg.get();

    v_neg *= -1;
    result.neg_after_mul_equal = v_neg.get();

    auto v_test = reaction::var(test_initial);
    auto old1 = v_test++;
    auto old2 = v_test--;
    result.post_inc_old1 = old1;
    result.post_dec_old2 = old2;
    result.final_v_test_value = v_test.get();

    return result;
}

} // namespace operator_test_functions

