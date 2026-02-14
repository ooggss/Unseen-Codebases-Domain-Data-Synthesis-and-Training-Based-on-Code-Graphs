

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
 * Function: create_division_batch_operation_expression
 *
 * Builds the core reactive objects used in the division in batch operations test.
 *
 * @return a tuple containing:
 *   - numerator: integer reactive variable
 *   - denominator: integer reactive variable
 *   - result: expression node for numerator / denominator
 */
auto create_division_batch_operation_expression() {
    auto numerator = var(15).setName("numerator");
    auto denominator = var(4).setName("denominator");
    auto result = expr(numerator / denominator).setName("result");

    return std::make_tuple(numerator, denominator, result);
}

}  // namespace expression_division_impl

