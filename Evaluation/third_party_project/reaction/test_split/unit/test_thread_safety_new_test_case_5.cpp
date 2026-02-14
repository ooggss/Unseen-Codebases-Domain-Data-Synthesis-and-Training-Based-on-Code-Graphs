

#include <gtest/gtest.h>
#include <tuple>

// include implementation
#include "test_thread_safety_function_implementation_5.hpp"

TEST(ThreadSafetyTest, SharedDependencyGraphConcurrency) {
    std::cout << "=== Shared Dependency Graph Concurrency Test ===" << std::endl;

    int operationsCompleted;
    bool raceDetected;
    int exceptionCount;

    std::tie(operationsCompleted, raceDetected, exceptionCount) =
        runSharedDependencyGraphConcurrencyScenario();

    const int numThreads = 3;
    const int operationsPerThread = 100;

    std::cout << "=== Shared Dependency Graph Concurrency Test Results ===" << std::endl;
    std::cout << "Total operations completed: " << operationsCompleted << std::endl;
    std::cout << "Expected operations: " << (numThreads * operationsPerThread) << std::endl;
    std::cout << "Exceptions caught: " << exceptionCount << std::endl;
    std::cout << "Race conditions detected: " << (raceDetected ? "Yes" : "No") << std::endl;

    EXPECT_EQ(operationsCompleted, numThreads * operationsPerThread);
    EXPECT_FALSE(raceDetected) << "Race conditions detected in shared dependency graph operations";
    EXPECT_EQ(exceptionCount, 0) << "Unexpected exceptions occurred during shared dependency graph operations";

    std::cout << "✅ Shared dependency graph concurrency test passed" << std::endl;
}

