#pragma once

#include <reaction/core/resource.h>

namespace test_reaction {

struct ResourceAtomicResult {
    int finalValue;
    bool operationReportedChange;
};

/**
 * Function: Use Resource::atomicOperation to update the stored value.
 *
 * @param initialValue Starting value for the resource
 * @param delta Amount to add through the atomic operation
 * @return ResourceAtomicResult Final value and whether the operation flagged a change
 */
ResourceAtomicResult test_resource_atomic(int initialValue, int delta) {
    reaction::Resource<int> resource(initialValue);
    bool operationChanged = false;

    resource.atomicOperation([&](int &value) {
        const int before = value;
        value += delta;
        operationChanged = (value != before);
        return operationChanged;
    });

    return ResourceAtomicResult{
        .finalValue = resource.getValue(),
        .operationReportedChange = operationChanged,
    };
}

}  // namespace test_reaction


