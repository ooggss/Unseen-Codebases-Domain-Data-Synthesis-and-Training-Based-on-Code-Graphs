

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

namespace expression_division_impl {

using namespace reaction;

/**
 * Function: create_complex_expression_chain_divisions
 *
 * Builds the core reactive objects used in the complex expression chains test.
 *
 * @return a tuple containing:
 *   - a: integer reactive variable
 *   - b: integer reactive variable
 *   - c: integer reactive variable
 *   - complexExpr1: expression node for (a / b) + c
 *   - complexExpr2: expression node for a / (b + c)
 *   - complexExpr3: expression node for (a / b) / c
 */
auto create_complex_expression_chain_divisions() {
    auto a = var(10).setName("a");
    auto b = var(3).setName("b");
    auto c = var(2).setName("c");

    auto complexExpr1 = expr((a / b) + c).setName("complexExpr1");
    auto complexExpr2 = expr(a / (b + c)).setName("complexExpr2");
    auto complexExpr3 = expr((a / b) / c).setName("complexExpr3");

    return std::make_tuple(a, b, c, complexExpr1, complexExpr2, complexExpr3);
}

}  // namespace expression_division_impl

