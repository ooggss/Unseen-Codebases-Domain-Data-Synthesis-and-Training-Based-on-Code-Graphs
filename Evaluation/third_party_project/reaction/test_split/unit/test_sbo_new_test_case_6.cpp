

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "reaction/memory/sbo_resource.h"
#include "reaction/memory/stack_monitor.h"
#include "reaction/memory/memory_config.h"
#include <memory>

// Include function implementation
#include "test_sbo_function_implementation_6.hpp"

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

TEST_F(SBOTest, SBOResourceUninitialized) {
    auto r = run_sbo_resource_uninitialized();

    EXPECT_TRUE(r.get_value_threw);
    EXPECT_TRUE(r.get_raw_ptr_threw);
    EXPECT_TRUE(r.first_update_succeeded);
    EXPECT_EQ(r.value_after_update, 42);
    EXPECT_EQ(r.dereferenced_raw_value, 42);
}

