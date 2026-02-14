

#include <gtest/gtest.h>
#include <tuple>

// include implementation
#include "test_thread_safety_function_implementation_8.hpp"

TEST(ThreadSafetyTest, ResetInvalidationConcurrency) {
    std::cout << "=== Reset Invalidation Concurrency Test ===" << std::endl;

    // We still verify initial state as in original test
    auto &manager = reaction::ThreadManager::getInstance();
    manager.resetForTesting();
    manager.resetForTesting(); // ensure clean, but core will reset again

    int readCount;
    int invalidationErrors;
    int finalVarValue;
    int finalExprValue;
    int finalDependentValue;

    std::tie(readCount,
             invalidationErrors,
             finalVarValue,
             finalExprValue,
             finalDependentValue) =
        runResetInvalidationConcurrencyScenario();

    std::cout << "=== Reset Invalidation Concurrency Test Results ===" << std::endl;
    std::cout << "Read operations: " << readCount << std::endl;
    std::cout << "Invalidation errors: " << invalidationErrors << std::endl;

    EXPECT_EQ(finalVarValue, 20);
    EXPECT_EQ(finalExprValue, 60);
    EXPECT_EQ(finalDependentValue, 180);

    std::cout << "✅ Reset invalidation concurrency test completed" << std::endl;
}

