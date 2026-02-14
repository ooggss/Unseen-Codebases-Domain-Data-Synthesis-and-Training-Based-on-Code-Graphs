#pragma once

#include <reaction/memory/memory_config.h>
#include <reaction/memory/stack_monitor.h>

namespace test_reaction {

struct StackAllocationSnapshot {
    bool smallAllowedWithoutMonitoring;
    bool largeAllowedWithoutMonitoring;
    bool runtimeAllowedWithoutMonitoring;
    bool largeAllowedWithMonitoring;
    bool guardSucceeded;
    bool allocationBlockedAtLimit;
    bool runtimeAllowedAfterRelease;
};

/**
 * Function: Demonstrate StackMonitor::canAllocate behaviour across modes.
 *
 * @param largeSize Value used for runtime canAllocate after release
 * @return StackAllocationSnapshot Snapshot of allocation checks before/after guard
 */
inline StackAllocationSnapshot test_stack_monitor_capacity(std::size_t largeSize) {
    using reaction::memory::SBOConfig;
    using reaction::memory::StackMonitor;

    StackMonitor::setMonitoringEnabled(false);
    StackMonitor::initialize();

    bool smallAllowedWithoutMonitoring = StackMonitor::canAllocate<16>();
    bool largeAllowedWithoutMonitoring = StackMonitor::canAllocate<128>();
    bool runtimeAllowedWithoutMonitoring = StackMonitor::canAllocate(SBOConfig::CONDITIONAL_SBO_SIZE);

    StackMonitor::setMonitoringEnabled(true);
    StackMonitor::initialize();

    bool largeAllowedWithMonitoring = StackMonitor::canAllocate<SBOConfig::MAX_SBO_STACK_USAGE / 2>();

    bool guardSucceeded = false;
    bool allocationBlockedAtLimit = false;

    {
        StackMonitor::StackGuard<SBOConfig::MAX_SBO_STACK_USAGE> guard;
        guardSucceeded = guard.success();
        allocationBlockedAtLimit = !StackMonitor::canAllocate<64>();
    }

    bool runtimeAllowedAfterRelease = StackMonitor::canAllocate(largeSize);

    return StackAllocationSnapshot{
        .smallAllowedWithoutMonitoring = smallAllowedWithoutMonitoring,
        .largeAllowedWithoutMonitoring = largeAllowedWithoutMonitoring,
        .runtimeAllowedWithoutMonitoring = runtimeAllowedWithoutMonitoring,
        .largeAllowedWithMonitoring = largeAllowedWithMonitoring,
        .guardSucceeded = guardSucceeded,
        .allocationBlockedAtLimit = allocationBlockedAtLimit,
        .runtimeAllowedAfterRelease = runtimeAllowedAfterRelease,
    };
}

}  // namespace test_reaction

