

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "reaction/memory/stack_monitor.h"
#include "reaction/memory/memory_config.h"

using namespace reaction;
using namespace reaction::memory;

/**
 * Result structure for StackMonitorOverflowProtection test.
 */
struct StackMonitorOverflowProtectionResult {
    size_t large_size;
    bool can_allocate_large;
    bool guard_success;
    size_t final_usage;
};

/**
 * Function: exercise overflow protection behavior of StackMonitor.
 */
StackMonitorOverflowProtectionResult run_stack_monitor_overflow_protection() {
    StackMonitorOverflowProtectionResult result{};
    result.large_size = SBOConfig::MAX_SBO_STACK_USAGE + 1;

    result.can_allocate_large = StackMonitor::canAllocate(result.large_size);

    StackMonitor::StackGuard<
        static_cast<std::size_t>(SBOConfig::MAX_SBO_STACK_USAGE + 1)> guard;
    result.guard_success = guard.success();
    result.final_usage   = StackMonitor::getCurrentUsage();

    return result;
}

