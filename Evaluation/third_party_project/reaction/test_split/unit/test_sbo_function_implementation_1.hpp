

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "reaction/memory/stack_monitor.h"
#include "reaction/memory/memory_config.h"

using namespace reaction;
using namespace reaction::memory;

/**
 * Result structure for StackMonitorBasics test.
 */
struct StackMonitorBasicsResult {
    size_t initial_usage;
    bool can_allocate_16;
    bool can_allocate_32;
    bool guard1_success;
    size_t usage_after_guard1;
    bool guard2_success;
    size_t usage_after_guard2;
    size_t usage_after_guard2_scope;
    size_t final_usage;
};

/**
 * Function: exercise basic StackMonitor behavior and return observed values.
 */
StackMonitorBasicsResult run_stack_monitor_basics() {
    StackMonitorBasicsResult result{};

    result.initial_usage   = StackMonitor::getCurrentUsage();
    result.can_allocate_16 = StackMonitor::canAllocate<16>();
    result.can_allocate_32 = StackMonitor::canAllocate(32);

    {
        StackMonitor::StackGuard<16> guard;
        result.guard1_success      = guard.success();
        result.usage_after_guard1  = StackMonitor::getCurrentUsage();

        {
            StackMonitor::StackGuard<32> guard2;
            result.guard2_success     = guard2.success();
            result.usage_after_guard2 = StackMonitor::getCurrentUsage();
        }
        result.usage_after_guard2_scope = StackMonitor::getCurrentUsage();
    }
    result.final_usage = StackMonitor::getCurrentUsage();

    return result;
}

