

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "reaction/memory/stack_monitor.h"
#include "reaction/memory/memory_config.h"

// Include function implementation
#include "test_sbo_function_implementation_1.hpp"

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

TEST_F(SBOTest, StackMonitorBasics) {
    auto r = run_stack_monitor_basics();

    EXPECT_EQ(r.initial_usage, 0u);
    EXPECT_TRUE(r.can_allocate_16);
    EXPECT_TRUE(r.can_allocate_32);
    EXPECT_TRUE(r.guard1_success);
    EXPECT_EQ(r.usage_after_guard1, 16u);
    EXPECT_TRUE(r.guard2_success);
    EXPECT_EQ(r.usage_after_guard2, 48u);
    EXPECT_EQ(r.usage_after_guard2_scope, 16u);
    EXPECT_EQ(r.final_usage, 0u);
}

