

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "reaction/memory/stack_monitor.h"
#include "reaction/memory/memory_config.h"

// Include function implementation
#include "test_sbo_function_implementation_2.hpp"

using namespace reaction;
using namespace reaction::memory;

class SBOTest : public ::testing::Test {
protected:
    void SetUp() override {
        StackMonitor::initialize();
    }
    void TearDown() override {
        StackMonitor::setMonitoringEnabled(false);
    }
};

TEST_F(SBOTest, StackMonitorOverflowProtection) {
    auto r = run_stack_monitor_overflow_protection();

    EXPECT_EQ(r.large_size, SBOConfig::MAX_SBO_STACK_USAGE + 1);
    EXPECT_FALSE(r.can_allocate_large);
    EXPECT_FALSE(r.guard_success);
    EXPECT_EQ(r.final_usage, 0u);
}

