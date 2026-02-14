

#include <gtest/gtest.h>
#include <tuple>

// include implementation
#include "test_thread_safety_function_implementation_0.hpp"

TEST(ThreadSafetyTest, SingleThreadAutoDisable) {
    std::cout << "=== Single-thread Auto-disable Test ===" << std::endl;

    bool initialState;
    int value1;
    int value2;
    bool afterSingleThread;

    std::tie(initialState, value1, value2, afterSingleThread) =
        runSingleThreadAutoDisableScenario();

    std::cout << "Thread safety state at test start: "
              << (initialState ? "Enabled" : "Disabled") << std::endl;
    std::cout << "Thread safety state after single-thread operations: "
              << (afterSingleThread ? "Enabled" : "Disabled") << std::endl;

    EXPECT_EQ(value1, 42);
    EXPECT_EQ(value2, 100);
    EXPECT_FALSE(afterSingleThread) << "Thread safety should be disabled in single-thread mode";

    std::cout << "✅ Single-thread auto-disable test passed" << std::endl;
}

