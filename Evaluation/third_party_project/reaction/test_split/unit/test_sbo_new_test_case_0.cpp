

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include "reaction/memory/sbo_resource.h"
#include "reaction/memory/stack_monitor.h"
#include "reaction/memory/memory_config.h"
#include <cstring>
#include <memory>

// Include function implementation (would normally be via header)
#include "test_sbo_function_implementation_0.hpp"

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

TEST_F(SBOTest, SBOTraitsBasicTypes) {
    // Call function to collect trait info
    auto result = run_sbo_traits_basic_types();

    // Original assertions
    EXPECT_TRUE(result.int_is_sbo_eligible);
    EXPECT_TRUE(result.int_always_sbo);
    EXPECT_FALSE(result.int_conditional_sbo);

    EXPECT_TRUE(result.double_is_sbo_eligible);
    EXPECT_TRUE(result.double_always_sbo);

    EXPECT_TRUE(result.smallstruct_is_sbo_eligible);
    EXPECT_TRUE(result.smallstruct_always_sbo);

    EXPECT_TRUE(result.mediumstruct_is_sbo_eligible);
    EXPECT_FALSE(result.mediumstruct_always_sbo);
    EXPECT_TRUE(result.mediumstruct_conditional_sbo);

    EXPECT_FALSE(result.largestruct_is_sbo_eligible);
    EXPECT_TRUE(result.largestruct_force_heap);

    EXPECT_TRUE(result.string_force_heap);
    EXPECT_TRUE(result.vector_force_heap);
}

