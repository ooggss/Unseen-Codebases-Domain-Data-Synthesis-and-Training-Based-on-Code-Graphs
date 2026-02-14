#pragma once

#include <reaction/core/resource.h>

namespace test_reaction {

struct ResourcePointerSnapshot {
    int initialPointerValue;
    int pointerValueAfterWrite;
    bool pointerStable;
};

/**
 * Function: Inspect Resource::getRawPtr and verify direct pointer writes.
 *
 * @param initialValue Initial integer stored inside the resource
 * @param directWriteValue Value assigned through the raw pointer
 * @return ResourcePointerSnapshot Snapshot describing pointer reads/writes
 */
inline ResourcePointerSnapshot test_resource_pointer_view(int initialValue, int directWriteValue) {
    reaction::Resource<int> resource(initialValue);

    int *rawPtrFirst = resource.getRawPtr();
    const int initialPointerValue = *rawPtrFirst;

    *rawPtrFirst = directWriteValue;

    int *rawPtrSecond = resource.getRawPtr();
    const int pointerValueAfterWrite = *rawPtrSecond;

    return ResourcePointerSnapshot{
        .initialPointerValue = initialPointerValue,
        .pointerValueAfterWrite = pointerValueAfterWrite,
        .pointerStable = rawPtrFirst == rawPtrSecond,
    };
}

}  // namespace test_reaction

