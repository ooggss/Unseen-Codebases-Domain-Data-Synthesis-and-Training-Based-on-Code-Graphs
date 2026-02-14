

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
 * Function: create_division_with_calculations
 *
 * Builds the core reactive objects used in the division with calculations test.
 *
 * @return a tuple containing:
 *   - x: integer reactive variable
 *   - y: integer reactive variable
 *   - sum: calculation node for x() + y()
 *   - diff: calculation node for x() - y()
 *   - ratio: expression node for sum / diff
 */
auto create_division_with_calculations() {
    auto x = var(6).setName("x");
    auto y = var(4).setName("y");

    // Create intermediate calculations
    auto sum = calc([=]() { return x() + y(); }).setName("sum");
    auto diff = calc([=]() { return x() - y(); }).setName("diff");

    // Division of calculations using expression templates
    auto ratio = expr(sum / diff).setName("ratio");

    return std::make_tuple(x, y, sum, diff, ratio);
}

}  // namespace expression_division_impl

