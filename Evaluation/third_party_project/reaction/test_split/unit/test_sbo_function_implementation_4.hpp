

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "reaction/memory/sbo_resource.h"
#include "reaction/memory/stack_monitor.h"
#include "reaction/memory/memory_config.h"
#include <memory>

using namespace reaction;
using namespace reaction::memory;

struct MediumStruct {
    double data[4];  // 32 bytes
    MediumStruct(double val = 0.0) {
        for (int i = 0; i < 4; ++i) data[i] = val + i;
    }
    bool operator==(const MediumStruct& other) const {
        for (int i = 0; i < 4; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }
    bool operator!=(const MediumStruct& other) const {
        return !(*this == other);
    }
};

/**
 * Result structure for SBOResourceMediumTypes test.
 */
struct SBOResourceMediumTypesResult {
    bool using_sbo_initial;
    MediumStruct value_initial;
    bool update_changed;
    MediumStruct value_after;
};

/**
 * Function: exercise SBOResource with MediumStruct (conditional SBO).
 */
SBOResourceMediumTypesResult run_sbo_resource_medium_types() {
    SBOResourceMediumTypesResult r{};
    auto resource = std::make_shared<SBOResource<MediumStruct>>(MediumStruct{1.0});

    r.using_sbo_initial = resource->isUsingSBO();
    r.value_initial     = resource->getValue();
    r.update_changed    = resource->updateValue(MediumStruct{2.0});
    r.value_after       = resource->getValue();

    return r;
}

