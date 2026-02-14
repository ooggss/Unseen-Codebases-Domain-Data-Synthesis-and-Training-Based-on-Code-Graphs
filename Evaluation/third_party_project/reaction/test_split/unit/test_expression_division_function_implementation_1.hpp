

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
 * Function: create_mixed_type_division_expressions
 *
 * Builds the core reactive objects used in the mixed-type division test.
 *
 * @return a tuple containing:
 *   - intVar: integer reactive variable
 *   - floatVar: double reactive variable
 *   - intByFloat: calculation node for intVar() / floatVar()
 *   - floatByInt: calculation node for floatVar() / intVar()
 */
auto create_mixed_type_division_expressions() {
    auto intVar = var(5).setName("intVar");
    auto floatVar = var(2.0).setName("floatVar");

    auto intByFloat =
        calc([=]() { return intVar() / floatVar(); }).setName("intByFloat");
    auto floatByInt =
        calc([=]() { return floatVar() / intVar(); }).setName("floatByInt");

    return std::make_tuple(intVar, floatVar, intByFloat, floatByInt);
}

}  // namespace expression_division_impl

