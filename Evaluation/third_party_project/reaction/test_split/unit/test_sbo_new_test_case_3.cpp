

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "reaction/memory/sbo_resource.h"
#include "reaction/memory/stack_monitor.h"
#include "reaction/memory/memory_config.h"
#include <memory>

// Include function implementation
#include "test_sbo_function_implementation_3.hpp"

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

TEST_F(SBOTest, SBOResourceSmallTypes) {
    auto r = run_sbo_resource_small_types();

    // int checks
    EXPECT_TRUE(r.int_using_sbo_initial);
    EXPECT_EQ(r.int_value_initial, 42);
    EXPECT_TRUE(r.int_update_100_changed);
    EXPECT_EQ(r.int_value_after_100, 100);
    EXPECT_FALSE(r.int_update_100_nochange);

    // SmallStruct checks
    EXPECT_TRUE(r.small_using_sbo_initial);
    EXPECT_EQ(r.small_value_initial, SmallStruct(10, 20));
    EXPECT_TRUE(r.small_update_changed);
    EXPECT_EQ(r.small_value_after, SmallStruct(30, 40));
}

