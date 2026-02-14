

#include <gtest/gtest.h>
#include <tuple>

// include implementation
#include "test_thread_safety_function_implementation_11.hpp"

TEST(ThreadSafetyTest, ConcurrentRandomReset) {
    std::cout << "=== Thread1 Stress Test ===" << std::endl;

    int calcResetOperations;
    int actionResetOperations;
    bool exceptionCaught;
    bool raceConditionDetected;
    bool threadSafetyEnabled;
    int testValue1;
    int testValue2;

    std::tie(calcResetOperations,
             actionResetOperations,
             exceptionCaught,
             raceConditionDetected,
             threadSafetyEnabled,
             testValue1,
             testValue2) =
        runConcurrentRandomResetScenario();

    constexpr int N = 50;
    constexpr int NUM_OPERATIONS_PER_THREAD = 10;

    std::cout << "=== Thread1 Stress Test Results ===" << std::endl;
    std::cout << "Calc reset operations completed: " << calcResetOperations << std::endl;
    std::cout << "Action reset operations completed: " << actionResetOperations << std::endl;
    std::cout << "Expected calc operations: " << (N * NUM_OPERATIONS_PER_THREAD) << std::endl;
    std::cout << "Expected action operations: " << (N * NUM_OPERATIONS_PER_THREAD) << std::endl;
    std::cout << "Exceptions caught: " << (exceptionCaught ? "Yes" : "No") << std::endl;
    std::cout << "Race conditions detected: " << (raceConditionDetected ? "Yes" : "No") << std::endl;
    std::cout << "Thread safety enabled during test: " << (threadSafetyEnabled ? "Yes" : "No") << std::endl;

    EXPECT_EQ(calcResetOperations, N * NUM_OPERATIONS_PER_THREAD)
        << "Not all calc reset operations completed";
    EXPECT_EQ(actionResetOperations, N * NUM_OPERATIONS_PER_THREAD)
        << "Not all action reset operations completed";
    EXPECT_FALSE(exceptionCaught)
        << "Exceptions were caught during stress test";
    EXPECT_FALSE(raceConditionDetected)
        << "Race conditions detected during stress test";
    EXPECT_TRUE(threadSafetyEnabled)
        << "Thread safety should be enabled after multi-threaded operations";

    EXPECT_GE(testValue1, 0) << "Var should return valid value after stress test";
    EXPECT_GE(testValue2, 0) << "Calc should return valid value after stress test";

    std::cout << "✅ Thread1 stress test passed" << std::endl;
}

