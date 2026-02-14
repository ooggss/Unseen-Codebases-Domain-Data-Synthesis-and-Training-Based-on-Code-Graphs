#pragma once

#include <cstddef>
#include <reaction/memory/stack_monitor.h>

namespace test_reaction {

struct StackMonitorReport {
    bool monitoringEnabledBefore;
    bool guardAllocated;
    std::size_t usageDuringGuard;
    std::size_t usageAfterGuard;
    double usagePercentage;
    bool nearLimitDuringGuard;
    bool monitoringAfterDisable;
};

/**
 * Function: Inspect StackMonitor behavior while toggling monitoring state.
 *
 * @return StackMonitorReport Snapshot of usage counters before/after guard scope.
 */
inline StackMonitorReport test_stack_monitor_guard() {
    using reaction::memory::StackMonitor;

    StackMonitor::setMonitoringEnabled(false);
    StackMonitor::initialize();

    StackMonitorReport report{};
    report.monitoringEnabledBefore = StackMonitor::isMonitoringEnabled();

    {
        StackMonitor::StackGuard<256> guard;
        report.guardAllocated = guard.success();
        report.usageDuringGuard = StackMonitor::getCurrentUsage();

        auto stats = StackMonitor::getStats();
        report.usagePercentage = stats.usage_percentage;
        report.nearLimitDuringGuard = stats.near_limit;
    }

    report.usageAfterGuard = StackMonitor::getCurrentUsage();

    StackMonitor::setMonitoringEnabled(false);
    report.monitoringAfterDisable = StackMonitor::isMonitoringEnabled();

    return report;
}

}  // namespace test_reaction

