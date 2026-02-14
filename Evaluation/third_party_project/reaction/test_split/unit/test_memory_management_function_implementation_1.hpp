

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

/**
 * Struct: MoveMemoryManagementResult
 *
 * Holds the observable results for testing move semantics of a reactive value.
 *
 * Fields:
 *   initial_value_after_move:
 *       The value of dds_move.get() immediately after moving from dds.
 *   dds_bool_after_move:
 *       Result of static_cast<bool>(dds) immediately after the move.
 *   throws_after_move:
 *       Whether calling dds.get() immediately after the move throws std::runtime_error.
 *   value_after_update:
 *       The value of dds_move.get() after a.value(2).
 *   dds_bool_after_update:
 *       Result of static_cast<bool>(dds) after the update.
 */
struct MoveMemoryManagementResult {
    std::string initial_value_after_move;
    bool dds_bool_after_move;
    bool throws_after_move;
    std::string value_after_update;
    bool dds_bool_after_update;
};

/**
 * Function: simulate_move_memory_management
 *
 * Purpose:
 *   Construct reactive variables, move a composed reactive value,
 *   and observe its behavior along with the moved-from object.
 *
 * Returns:
 *   MoveMemoryManagementResult containing all observable outcomes that
 *   the original test asserts on.
 */
MoveMemoryManagementResult simulate_move_memory_management() {
    MoveMemoryManagementResult result{};

    auto a = reaction::var(1);
    auto b = reaction::var(3.14);
    auto ds = reaction::calc(
        [](int aa, double bb) {
            return std::to_string(aa) + std::to_string(bb);
        },
        a, b);
    auto dds = reaction::calc(
        [](auto aa, auto dsds) {
            return std::to_string(aa) + dsds;
        },
        a, ds);

    auto dds_move = std::move(dds);

    // After move
    result.initial_value_after_move = dds_move.get();
    result.dds_bool_after_move = static_cast<bool>(dds);
    result.throws_after_move = false;
    try {
        (void)dds.get();
    } catch (const std::runtime_error&) {
        result.throws_after_move = true;
    }

    // After updating source
    a.value(2);
    result.value_after_update = dds_move.get();
    result.dds_bool_after_update = static_cast<bool>(dds);

    return result;
}

