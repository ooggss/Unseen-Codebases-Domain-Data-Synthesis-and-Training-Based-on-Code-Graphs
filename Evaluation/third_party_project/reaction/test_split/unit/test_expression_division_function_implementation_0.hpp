

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
 * Function: create_integer_division_promotion_expression
 *
 * Builds the core reactive objects used in the integer division promotion test.
 *
 * @return a tuple containing:
 *   - a: integer reactive variable
 *   - b: integer reactive variable
 *   - division: expression node representing a / b
 */
auto create_integer_division_promotion_expression() {
    auto a = var(1).setName("a");
    auto b = var(2).setName("b");
    auto division = expr(a / b).setName("division");

    return std::make_tuple(a, b, division);
}

}  // namespace expression_division_impl

