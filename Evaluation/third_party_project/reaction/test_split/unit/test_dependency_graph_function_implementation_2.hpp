

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

namespace dependency_graph_test_cycle_dependency {

/**
 * Function: test_cycle_dependency_throws
 *
 * Encapsulates the logic that was previously inside the
 * DependencyGraphTest.TestCycleDependency test body.
 *
 * @return true if the final reset call throws std::runtime_error, false otherwise.
 */
bool test_cycle_dependency_throws() {
    auto a = reaction::var(1);
    auto b = reaction::var(2);
    auto c = reaction::var(3);

    auto dsA = reaction::calc([](int bb) { return bb; }, b);

    auto dsB = reaction::calc([](int cc) { return cc; }, c);

    auto dsC = reaction::calc([](int aa) { return aa; }, a);

    dsA.reset([&]() { return b() + dsB(); });

    dsB.reset([&]() { return c() * dsC(); });

    try {
        dsC.reset([&]() { return a() - dsA(); });
    } catch (const std::runtime_error&) {
        return true;
    } catch (...) {
        // Threw some other exception
        return false;
    }
    // No exception thrown
    return false;
}

}  // namespace dependency_graph_test_cycle_dependency

