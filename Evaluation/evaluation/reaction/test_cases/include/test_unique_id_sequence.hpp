#pragma once

#include <reaction/core/id_generator.h>

namespace test_reaction {

struct UniqueIdSequence {
    uint64_t firstValue;
    uint64_t secondValue;
    uint64_t thirdValue;
    bool strictlyIncreasing;
};

/**
 * Function: Generate multiple UniqueID instances and capture their values.
 *
 * @return UniqueIdSequence The generated values and monotonicity flag.
 */
UniqueIdSequence test_unique_id_sequence() {
    using namespace reaction;

    UniqueID first;
    UniqueID second;
    UniqueID third;

    const uint64_t firstValue = first.value();
    const uint64_t secondValue = static_cast<uint64_t>(second);
    const uint64_t thirdValue = third.value();

    const bool increasing = firstValue < secondValue && secondValue < thirdValue;

    return UniqueIdSequence{
        .firstValue = firstValue,
        .secondValue = secondValue,
        .thirdValue = thirdValue,
        .strictlyIncreasing = increasing,
    };
}

}  // namespace test_reaction


