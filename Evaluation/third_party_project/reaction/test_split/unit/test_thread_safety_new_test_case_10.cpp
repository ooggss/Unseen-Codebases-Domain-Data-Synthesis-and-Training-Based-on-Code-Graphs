

#include <gtest/gtest.h>
#include <tuple>

// include implementation
#include "test_thread_safety_function_implementation_10.hpp"

TEST(ThreadSafetyTest, ConcurrentReactiveOperations) {
    std::cout << "=== Concurrent Reactive Operations Test ===" << std::endl;

    int operationsCompleted;
    bool raceDetected;
    bool someCalcsUpdated;

    std::tie(operationsCompleted, raceDetected, someCalcsUpdated) =
        runConcurrentReactiveOperationsScenario();

    const int numThreadsPerType = 5;
    std::cout << "=== Concurrent Reactive Operations Test Results ===" << std::endl;
    std::cout << "Total operations completed: " << operationsCompleted << std::endl;
    std::cout << "Expected operations: " << (numThreadsPerType * 2 * 5) << std::endl;
    std::cout << "Race conditions detected: " << (raceDetected ? "Yes" : "No") << std::endl;

    EXPECT_EQ(operationsCompleted, numThreadsPerType * 2 * 5);
    EXPECT_FALSE(raceDetected) << "Race conditions detected during concurrent reactive operations";
    EXPECT_TRUE(someCalcsUpdated) << "No calculations appear to have been updated during concurrent operations";

    std::cout << "✅ Concurrent reactive operations test passed" << std::endl;
}

