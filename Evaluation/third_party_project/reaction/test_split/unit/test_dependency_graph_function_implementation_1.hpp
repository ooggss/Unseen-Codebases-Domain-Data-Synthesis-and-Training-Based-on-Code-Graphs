

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

namespace dependency_graph_test_self_dependency {

/**
 * Function: test_self_dependency_throws
 *
 * Encapsulates the logic that was previously inside the
 * DependencyGraphTest.TestSelfDependency test body.
 *
 * @return true if the reset call throws std::runtime_error, false otherwise.
 */
bool test_self_dependency_throws() {
    auto a = reaction::var(1);
    auto dsA = reaction::calc([](int aa) { return aa; }, a);

    try {
        dsA.reset([&]() { return a() + dsA(); });
    } catch (const std::runtime_error&) {
        return true;
    } catch (...) {
        // Threw some other exception
        return false;
    }
    // No exception thrown
    return false;
}

}  // namespace dependency_graph_test_self_dependency

