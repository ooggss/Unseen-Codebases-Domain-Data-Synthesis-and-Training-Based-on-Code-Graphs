

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "reaction/memory/sbo_resource.h"
#include "reaction/memory/stack_monitor.h"
#include "reaction/memory/memory_config.h"
#include <memory>
#include <cstring>

using namespace reaction;
using namespace reaction::memory;

struct LargeStruct {
    char data[128];  // 128 bytes - should force heap allocation
    LargeStruct(char fill = 'A') {
        std::fill(data, data + 128, fill);
    }
    bool operator==(const LargeStruct& other) const {
        return std::memcmp(data, other.data, 128) == 0;
    }
    bool operator!=(const LargeStruct& other) const {
        return !(*this == other);
    }
};

/**
 * Result structure for SBOResourceLargeTypes test.
 */
struct SBOResourceLargeTypesResult {
    bool using_sbo_initial;
    LargeStruct value_initial;
    bool update_changed;
    LargeStruct value_after;
};

/**
 * Function: exercise SBOResource with LargeStruct (heap-only).
 */
SBOResourceLargeTypesResult run_sbo_resource_large_types() {
    SBOResourceLargeTypesResult r{};
    auto resource = std::make_shared<SBOResource<LargeStruct>>(LargeStruct{'X'});

    r.using_sbo_initial = resource->isUsingSBO();
    r.value_initial     = resource->getValue();
    r.update_changed    = resource->updateValue(LargeStruct{'Y'});
    r.value_after       = resource->getValue();

    return r;
}

