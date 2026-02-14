

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "reaction/memory/sbo_resource.h"
#include "reaction/memory/stack_monitor.h"
#include "reaction/memory/memory_config.h"
#include <memory>

using namespace reaction;
using namespace reaction::memory;

struct SmallStruct {
    int x, y;
    SmallStruct(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator==(const SmallStruct& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const SmallStruct& other) const {
        return !(*this == other);
    }
};

/**
 * Result structure for SBOResourceSmallTypes test.
 */
struct SBOResourceSmallTypesResult {
    // int
    bool int_using_sbo_initial;
    int  int_value_initial;
    bool int_update_100_changed;
    int  int_value_after_100;
    bool int_update_100_nochange;

    // SmallStruct
    bool small_using_sbo_initial;
    SmallStruct small_value_initial;
    bool small_update_changed;
    SmallStruct small_value_after;
};

/**
 * Function: exercise SBOResource with small types (int and SmallStruct).
 */
SBOResourceSmallTypesResult run_sbo_resource_small_types() {
    SBOResourceSmallTypesResult r{};

    // int
    {
        auto resource = std::make_shared<SBOResource<int>>(42);
        r.int_using_sbo_initial    = resource->isUsingSBO();
        r.int_value_initial        = resource->getValue();
        r.int_update_100_changed   = resource->updateValue(100);
        r.int_value_after_100      = resource->getValue();
        r.int_update_100_nochange  = resource->updateValue(100);
    }

    // SmallStruct
    {
        auto resource = std::make_shared<SBOResource<SmallStruct>>(SmallStruct{10, 20});
        r.small_using_sbo_initial  = resource->isUsingSBO();
        r.small_value_initial      = resource->getValue();
        r.small_update_changed     = resource->updateValue(SmallStruct{30, 40});
        r.small_value_after        = resource->getValue();
    }

    return r;
}

