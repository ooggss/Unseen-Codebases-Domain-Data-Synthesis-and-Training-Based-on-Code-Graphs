#pragma once

#include <reaction/expression/atomic_operations.h>
#include <cstdint>

namespace test_reaction {

/**
 * Struct: AtomicHelperSnapshot
 *
 * Records the value of an integer after a sequence of atomic compound helper
 * operations and whether each operation reported a change.
 */
struct AtomicHelperSnapshot {
    int32_t finalValue;
    bool addReportedChange;
    bool multiplyReportedChange;
    bool andReportedChange;
    bool leftShiftReportedChange;
    bool incrementReportedChange;
};

/**
 * Helper implementation type that mimics the minimal interface required by
 * reaction::atomicCompoundAssign helpers. It stores an integer and exposes
 * an atomicOperation method that receives a lambda and tracks whether the
 * value was changed.
 */
class IntAtomicImpl {
public:
    explicit IntAtomicImpl(int32_t initial) : m_value(initial) {}

    template <typename F>
    void atomicOperation(F&& op) {
        m_lastReportedChange = op(m_value);
    }

    template <typename F>
    void atomicOperation(F&& op, bool /*forceNotify*/) {
        m_lastReportedChange = op(m_value);
    }

    int32_t value() const { return m_value; }
    bool lastReportedChange() const { return m_lastReportedChange; }

private:
    int32_t m_value;
    bool m_lastReportedChange = false;
};

/**
 * Function: test_atomic_compound_helpers
 *
 * Demonstrates the low-level atomic compound helper APIs:
 * - atomicCompoundAssign
 * - atomicAddAssign
 * - atomicMultiplyAssign
 * - atomicBitwiseAndAssign
 * - atomicLeftShiftAssign
 * - atomicIncrement
 *
 * These helpers operate on a simple IntAtomicImpl type instead of a full
 * React wrapper, making it easy to observe value and change reporting.
 *
 * @param initial Initial integer value
 * @return AtomicHelperSnapshot
 *         Snapshot containing the final value and which operations reported
 *         that a change occurred.
 */
inline AtomicHelperSnapshot test_atomic_compound_helpers(int32_t initial) {
    using namespace reaction;

    IntAtomicImpl impl(initial);

    // Direct atomicCompoundAssign with an AddAssignOp.
    atomicCompoundAssign<AddAssignOp>(impl, 3);
    const bool addChanged = impl.lastReportedChange();

    // Use the macro-generated helpers for several operations.
    atomicMultiplyAssign(impl, 2);
    const bool mulChanged = impl.lastReportedChange();

    atomicBitwiseAndAssign(impl, 0xFF);
    const bool andChanged = impl.lastReportedChange();

    atomicLeftShiftAssign(impl, 1);
    const bool shiftChanged = impl.lastReportedChange();

    // Finally, increment the value using atomicIncrement.
    atomicIncrement(impl);
    const bool incChanged = impl.lastReportedChange();

    return AtomicHelperSnapshot{
        .finalValue = impl.value(),
        .addReportedChange = addChanged,
        .multiplyReportedChange = mulChanged,
        .andReportedChange = andChanged,
        .leftShiftReportedChange = shiftChanged,
        .incrementReportedChange = incChanged,
    };
}

}  // namespace test_reaction


