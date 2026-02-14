

#include <gtest/gtest.h>
#include <tuple>

// include implementation
#include "test_thread_safety_function_implementation_9.hpp"

TEST(ThreadSafetyTest, VarIncrementConcurrency) {
    std::cout << "=== Var Increment Concurrency Test ===" << std::endl;

    int finalValue;
    int totalOperationsPerformed;
    int threadsCompleted;
    bool raceDetected;

    std::tie(finalValue,
             totalOperationsPerformed,
             threadsCompleted,
             raceDetected) =
        runVarIncrementConcurrencyScenario();

    const int numThreads = 4;
    const int incrementsPerThread = 50;

    std::cout << "=== Var Increment Concurrency Test Results ===" << std::endl;
    std::cout << "Total operations performed: " << totalOperationsPerformed << std::endl;
    std::cout << "Expected operations: " << (numThreads * incrementsPerThread) << std::endl;
    std::cout << "Final counter value: " << finalValue << std::endl;
    std::cout << "Threads completed: " << threadsCompleted << std::endl;
    std::cout << "Race conditions detected: " << (raceDetected ? "Yes" : "No") << std::endl;

    EXPECT_EQ(threadsCompleted, numThreads);
    EXPECT_EQ(totalOperationsPerformed, numThreads * incrementsPerThread);
    EXPECT_FALSE(raceDetected) << "Race conditions detected during increment operations";
    EXPECT_EQ(finalValue, numThreads * incrementsPerThread)
        << "Atomic increment should ensure final value equals expected operations";

    std::cout << "✅ Var increment concurrency test passed" << std::endl;
}

