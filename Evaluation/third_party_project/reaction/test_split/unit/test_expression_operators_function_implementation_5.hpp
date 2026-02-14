

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

namespace expression_operators_impl {

using namespace reaction;

/**
 * Execute expressions to test operator precedence and associativity and
 * return their evaluated results.
 */
struct OperatorPrecedenceResult {
    bool prec_expr1;
    int prec_expr2;
    bool prec_expr3;
};

OperatorPrecedenceResult run_operator_precedence_scenario() {
    auto a = var(2).setName("a");
    auto b = var(3).setName("b");
    auto c = var(4).setName("c");

    // Test arithmetic precedence with comparison
    auto prec_expr1 = expr(a + b * c > 10).setName("prec_expr1");

    // Test unary precedence
    auto prec_expr2 = expr(-a + b).setName("prec_expr2");

    // Test logical precedence
    auto bool1 = var(true).setName("bool1");
    auto bool2 = var(false).setName("bool2");
    auto bool3 = var(true).setName("bool3");

    auto prec_expr3 = expr(bool1 || bool2 && bool3).setName("prec_expr3");

    OperatorPrecedenceResult result{
        .prec_expr1 = prec_expr1.get(), // 2 + (3*4) = 14 > 10 is true
        .prec_expr2 = prec_expr2.get(), // (-2) + 3 = 1
        .prec_expr3 = prec_expr3.get()  // true || (false && true) = true
    };

    return result;
}

} // namespace expression_operators_impl

