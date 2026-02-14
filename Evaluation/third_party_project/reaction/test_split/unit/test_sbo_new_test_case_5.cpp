

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "reaction/memory/sbo_resource.h"
#include "reaction/memory/stack_monitor.h"
#include "reaction/memory/memory_config.h"
#include <memory>
#include <cstring>

// Include function implementation
#include "test_sbo_function_implementation_5.hpp"

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

TEST_F(SBOTest, SBOResourceLargeTypes) {
    auto r = run_sbo_resource_large_types();

    EXPECT_FALSE(r.using_sbo_initial);
    EXPECT_EQ(r.value_initial, LargeStruct('X'));
    EXPECT_TRUE(r.update_changed);
    EXPECT_EQ(r.value_after, LargeStruct('Y'));
}

