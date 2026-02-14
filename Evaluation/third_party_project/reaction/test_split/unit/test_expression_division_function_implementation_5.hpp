

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
 * Function: create_division_edge_case_expression
 *
 * Builds the core reactive objects used in the division edge cases test.
 *
 * @return a tuple containing:
 *   - a: integer reactive variable
 *   - b: integer reactive variable
 *   - zeroDiv: expression node for a / b
 */
auto create_division_edge_case_expression() {
    auto a = var(0).setName("a");
    auto b = var(5).setName("b");

    auto zeroDiv = expr(a / b).setName("zeroDiv");

    return std::make_tuple(a, b, zeroDiv);
}

}  // namespace expression_division_impl

