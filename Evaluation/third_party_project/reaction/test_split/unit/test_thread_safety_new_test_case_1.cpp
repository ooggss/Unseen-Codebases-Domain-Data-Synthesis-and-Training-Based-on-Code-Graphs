

#include <gtest/gtest.h>
#include <tuple>

// include implementation
#include "test_thread_safety_function_implementation_1.hpp"

TEST(ThreadSafetyTest, MultiThreadAutoEnable) {
    std::cout << "=== Multi-thread Auto-enable Test ===" << std::endl;

    bool initialState;
    bool threadSafetyWasEnabled;
    bool afterMultiThread;
    int thread1Operations;
    int thread2Operations;

    std::tie(initialState,
             threadSafetyWasEnabled,
             afterMultiThread,
             thread1Operations,
             thread2Operations) = runMultiThreadAutoEnableScenario();

    std::cout << "Initial thread safety state: "
              << (initialState ? "Enabled" : "Disabled") << std::endl;
    std::cout << "Thread safety state after multi-thread operations: "
              << (afterMultiThread ? "Enabled" : "Disabled") << std::endl;
    std::cout << "Thread safety was enabled during execution: "
              << (threadSafetyWasEnabled ? "Yes" : "No") << std::endl;

    bool testPassed = afterMultiThread || threadSafetyWasEnabled;

    EXPECT_TRUE(testPassed) << "Thread safety should be enabled in multi-thread mode (either during or after execution)";
    EXPECT_EQ(thread1Operations, 100);
    EXPECT_EQ(thread2Operations, 100);

    std::cout << "✅ Multi-thread auto-enable test passed" << std::endl;
}

