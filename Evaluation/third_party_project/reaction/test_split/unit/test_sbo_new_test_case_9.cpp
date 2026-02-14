

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "reaction/memory/sbo_resource.h"
#include "reaction/memory/stack_monitor.h"
#include "reaction/memory/memory_config.h"
#include <memory>
#include <cstring>

// Include function implementation
#include "test_sbo_function_implementation_9.hpp"

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

TEST_F(SBOTest, StorageInfoDebugging) {
    auto r = run_storage_info_debugging();

    EXPECT_TRUE(r.sbo_using_sbo);
    EXPECT_TRUE(r.sbo_initialized);
    EXPECT_EQ(r.sbo_type_size, sizeof(SmallStruct));
    EXPECT_EQ(r.sbo_stack_usage, sizeof(SmallStruct));

    EXPECT_FALSE(r.heap_using_sbo);
    EXPECT_TRUE(r.heap_initialized);
    EXPECT_EQ(r.heap_type_size, sizeof(LargeStruct));
    EXPECT_EQ(r.heap_stack_usage, 0u);
}

