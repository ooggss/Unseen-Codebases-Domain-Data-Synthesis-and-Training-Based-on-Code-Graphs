

#include <gtest/gtest.h>
#include <tuple>

// include implementation
#include "test_thread_safety_function_implementation_2.hpp"

TEST(ThreadSafetyTest, SingleToMultiThreadTransition) {
    std::cout << "=== Single-to-Multi-thread Transition Test ===" << std::endl;

    bool initialState;
    int valueSingle;
    bool multiThreadOperations;
    int threadValue;
    bool finalState;
    int finalValue;

    std::tie(initialState,
             valueSingle,
             multiThreadOperations,
             threadValue,
             finalState,
             finalValue) =
        runSingleToMultiThreadTransitionScenario();

    std::cout << "Initial state: " << (initialState ? "Enabled" : "Disabled") << std::endl;
    std::cout << "Final state: " << (finalState ? "Enabled" : "Disabled") << std::endl;

    EXPECT_EQ(valueSingle, 42);
    EXPECT_TRUE(multiThreadOperations);
    EXPECT_EQ(threadValue, 100);
    EXPECT_EQ(finalValue, 100);

    std::cout << "✅ Single-to-Multi-thread transition test passed" << std::endl;
}

