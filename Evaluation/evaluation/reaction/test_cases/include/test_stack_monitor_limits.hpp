#pragma once

#include <reaction/memory/memory_config.h>
#include <reaction/memory/stack_monitor.h>

namespace test_reaction {

struct StackLimitSnapshot {
    reaction::memory::StackMonitor::UsageStats statsBeforeGuard;
    reaction::memory::StackMonitor::UsageStats statsAfterGuard;
    bool templateAllocationAllowed;
    bool runtimeAllocationAllowed;
    bool guardHeld;
    bool allocationBlockedWhileGuardHeld;
};

/**
 * Function: Inspect StackMonitor counters before/after a large guard.
 *
 * @return StackLimitSnapshot Usage stats and allocation checks
 */
inline StackLimitSnapshot test_stack_monitor_limits() {
    using reaction::memory::SBOConfig;
    using reaction::memory::StackMonitor;

    StackMonitor::setMonitoringEnabled(true);
    StackMonitor::initialize();

    const auto statsBefore = StackMonitor::getStats();
    const bool templateAllowed = StackMonitor::canAllocate<32>();
    const bool runtimeAllowed = StackMonitor::canAllocate(64);

    StackMonitor::StackGuard<SBOConfig::MAX_SBO_STACK_USAGE - 128> guard;
    const bool guardSuccess = guard.success();
    const bool blockedWhileGuard = !StackMonitor::canAllocate<256>();
    const auto statsAfterGuard = StackMonitor::getStats();

    return StackLimitSnapshot{
        .statsBeforeGuard = statsBefore,
        .statsAfterGuard = statsAfterGuard,
        .templateAllocationAllowed = templateAllowed,
        .runtimeAllocationAllowed = runtimeAllowed,
        .guardHeld = guardSuccess,
        .allocationBlockedWhileGuardHeld = blockedWhileGuard,
    };
}

}  // namespace test_reaction

