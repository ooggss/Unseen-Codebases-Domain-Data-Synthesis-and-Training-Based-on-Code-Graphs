

#include <gtest/gtest.h>

// Include function implementation
#include "test_sbo_function_implementation_7.hpp"

class SBOTest : public ::testing::Test {};

TEST_F(SBOTest, ResourceClassWithSBO) {
    auto r = run_resource_class_with_sbo();
    EXPECT_TRUE(r.placeholder);
}

