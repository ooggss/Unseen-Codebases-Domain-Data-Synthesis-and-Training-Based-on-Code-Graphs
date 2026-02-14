

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

namespace expression_operators_impl {

using namespace reaction;

/**
 * Execute complex operator combination expressions and return their evaluated
 * results, including dynamic update behavior.
 */
struct ComplexOperatorsResult {
    bool complex1_initial;
    int complex2_initial;
    bool complex3;
    bool complex4;
    bool complex1_after_update;
    int complex2_after_update;
};

ComplexOperatorsResult run_complex_operators_scenario() {
    auto x = var(4).setName("x");
    auto y = var(2).setName("y");
    auto z = var(6).setName("z");

    // Test arithmetic with comparisons
    auto complex1 = expr((x + y) > z).setName("complex1");

    // Test nested unary operators
    auto complex2 = expr(-(x - y)).setName("complex2");

    // Test logical with arithmetic comparisons
    auto complex3 = expr((x > y) && (z / y == 3)).setName("complex3");

    // Test chained comparisons with logical operators
    auto complex4 = expr((x < z) && (y < x) && (x < z)).setName("complex4");

    ComplexOperatorsResult result{
        .complex1_initial = complex1.get(), // (4+2) > 6 is false
        .complex2_initial = complex2.get(), // -(4-2) = -2
        .complex3 = complex3.get(),         // (4>2) && (6/2==3) is true
        .complex4 = complex4.get(),         // 2 < 4 < 6
        .complex1_after_update = false,
        .complex2_after_update = 0
    };

    // Update values and verify recalculation
    x.value(8);
    result.complex1_after_update = complex1.get();   // (8+2) > 6 is true
    result.complex2_after_update = complex2.get();   // -(8-2) = -6

    return result;
}

} // namespace expression_operators_impl

