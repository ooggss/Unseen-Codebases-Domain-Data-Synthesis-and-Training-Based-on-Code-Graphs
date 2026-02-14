

#include <gtest/gtest.h>
#include <tuple>

// include implementation
#include "test_thread_safety_function_implementation_6.hpp"

TEST(ThreadSafetyTest, SharedDependencyGraphReadOnly) {
    std::cout << "=== Shared Dependency Graph Read-Only Test ===" << std::endl;

    int initVal1, initVal2, initVal3;
    int operationsCompleted;
    bool raceDetected;
    int exceptionCount;
    int finalVal1, finalVal2, finalVal3;

    std::tie(initVal1, initVal2, initVal3,
             operationsCompleted, raceDetected, exceptionCount,
             finalVal1, finalVal2, finalVal3) =
        runSharedDependencyGraphReadOnlyScenario();

    const int EXPECTED_VAL1 = 42 + 24;                       // 66
    const int EXPECTED_VAL2 = 42 * 24;                       // 1008
    const int EXPECTED_VAL3 = EXPECTED_VAL1 + EXPECTED_VAL2; // 1074

    std::cout << "Pre-initializing expressions..." << std::endl;
    std::cout << "Initial values: expr1=" << initVal1
              << ", expr2=" << initVal2
              << ", expr3=" << initVal3 << std::endl;

    EXPECT_EQ(initVal1, EXPECTED_VAL1);
    EXPECT_EQ(initVal2, EXPECTED_VAL2);
    EXPECT_EQ(initVal3, EXPECTED_VAL3);

    const int numThreads = 4;
    const int operationsPerThread = 1000;

    std::cout << "=== Shared Dependency Graph Read-Only Test Results ===" << std::endl;
    std::cout << "Total operations completed: " << operationsCompleted << std::endl;
    std::cout << "Expected operations: " << (numThreads * operationsPerThread) << std::endl;
    std::cout << "Exceptions caught: " << exceptionCount << std::endl;
    std::cout << "Race conditions detected: " << (raceDetected ? "Yes" : "No") << std::endl;
    std::cout << "Final values: expr1=" << finalVal1
              << ", expr2=" << finalVal2
              << ", expr3=" << finalVal3 << std::endl;

    EXPECT_EQ(operationsCompleted, numThreads * operationsPerThread);
    EXPECT_EQ(finalVal1, EXPECTED_VAL1);
    EXPECT_EQ(finalVal2, EXPECTED_VAL2);
    EXPECT_EQ(finalVal3, EXPECTED_VAL3);
    EXPECT_FALSE(raceDetected) << "Race conditions or data corruption detected in read-only operations";
    EXPECT_EQ(exceptionCount, 0) << "Unexpected exceptions occurred during read-only operations";

    std::cout << "✅ Shared dependency graph read-only test passed" << std::endl;
}

