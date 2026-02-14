

#include <gtest/gtest.h>
#include <tuple>

// include implementation
#include "test_thread_safety_function_implementation_7.hpp"

TEST(ThreadSafetyTest, ResetInvalidationBasic) {
    std::cout << "=== Reset Invalidation Basic Test ===" << std::endl;

    int e1_i, e2_i, e3_i;
    int e1_r1, e2_r1, e3_r1;
    int e1_r2, e2_r2, e3_r2;

    std::tie(e1_i, e2_i, e3_i,
             e1_r1, e2_r1, e3_r1,
             e1_r2, e2_r2, e3_r2) =
        runResetInvalidationBasicScenario();

    EXPECT_EQ(e1_i, 20);
    EXPECT_EQ(e2_i, 60);
    EXPECT_EQ(e3_i, 80);

    std::cout << "Initial state: expr1=" << e1_i
              << ", expr2=" << e2_i
              << ", expr3=" << e3_i << std::endl;

    EXPECT_EQ(e1_r1, 50);
    EXPECT_EQ(e2_r1, 60);
    EXPECT_EQ(e3_r1, 110);

    std::cout << "After expr1 reset: expr1=" << e1_r1
              << ", expr2=" << e2_r1
              << ", expr3=" << e3_r1 << std::endl;

    EXPECT_EQ(e1_r2, 50);
    EXPECT_EQ(e2_r2, 40);
    EXPECT_EQ(e3_r2, 90);

    std::cout << "After expr2 reset: expr1=" << e1_r2
              << ", expr2=" << e2_r2
              << ", expr3=" << e3_r2 << std::endl;

    std::cout << "✅ Reset invalidation basic test passed" << std::endl;
}

