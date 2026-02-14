

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "reaction/memory/sbo_resource.h"
#include "reaction/memory/stack_monitor.h"
#include "reaction/memory/memory_config.h"
#include <memory>
#include <stdexcept>

using namespace reaction;
using namespace reaction::memory;

/**
 * Result structure for SBOResourceUninitialized test.
 */
struct SBOResourceUninitializedResult {
    bool get_value_threw;
    bool get_raw_ptr_threw;
    bool first_update_succeeded;
    int  value_after_update;
    int  dereferenced_raw_value;
};

/**
 * Function: exercise behavior of uninitialized SBOResource<int>.
 */
SBOResourceUninitializedResult run_sbo_resource_uninitialized() {
    SBOResourceUninitializedResult r{};
    auto resource = std::make_shared<SBOResource<int>>();

    // getValue should throw
    try {
        (void)resource->getValue();
        r.get_value_threw = false;
    } catch (const std::runtime_error&) {
        r.get_value_threw = true;
    }

    // getRawPtr should throw
    try {
        (void)resource->getRawPtr();
        r.get_raw_ptr_threw = false;
    } catch (const std::runtime_error&) {
        r.get_raw_ptr_threw = true;
    }

    r.first_update_succeeded = resource->updateValue(42);
    r.value_after_update     = resource->getValue();
    r.dereferenced_raw_value = *resource->getRawPtr();

    return r;
}

