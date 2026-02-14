#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

struct PointerAccessSnapshot {
    int valueAfterFirstAdd;
    int valueAfterSecondAdd;
    bool pointerStable;
};

/**
 * Function: Demonstrate pointer-style access for reactive structs.
 *
 * @param initialValue Initial value stored inside the Counter
 * @param delta Amount added on each pointer invocation
 * @return PointerAccessSnapshot Snapshot capturing results after pointer operations
 */
inline PointerAccessSnapshot test_react_pointer_access(int initialValue, int delta) {
    using namespace reaction;

    struct Counter {
        int value;
        void add(int d) { value += d; }
        int current() const { return value; }
    };

    auto counter = var(Counter{initialValue});

    auto firstPtr = counter.operator->();
    firstPtr->add(delta);
    const int afterFirst = counter().current();

    auto secondPtr = counter.operator->();
    secondPtr->add(delta);
    const int afterSecond = counter().current();

    return PointerAccessSnapshot{
        .valueAfterFirstAdd = afterFirst,
        .valueAfterSecondAdd = afterSecond,
        .pointerStable = firstPtr == secondPtr,
    };
}

}  // namespace test_reaction

