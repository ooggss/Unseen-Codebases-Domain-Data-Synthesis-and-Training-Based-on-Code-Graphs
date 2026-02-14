

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <string>
#include <vector>

namespace operator_test_functions {

/**
 * @brief Encapsulates results of string operator operations.
 */
struct StringOperatorsResult {
    std::string after_first_plus_equal;
    std::string after_second_plus_equal;
};

/**
 * @brief Execute string concatenation operations on a reactive var.
 *
 * @param initial Initial string value.
 * @return StringOperatorsResult Recorded string values after operations.
 */
StringOperatorsResult run_string_sequence(const std::string& initial) {
    StringOperatorsResult result{};
    auto str = reaction::var(initial);

    str += " World";
    result.after_first_plus_equal = str.get();

    str += "!";
    result.after_second_plus_equal = str.get();

    return result;
}

} // namespace operator_test_functions

