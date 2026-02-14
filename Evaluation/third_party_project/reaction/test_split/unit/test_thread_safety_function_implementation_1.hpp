

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

/**
 * Functional core for: ThreadSafetyTest.MultiThreadAutoEnable
 *
 * @return tuple:
 *   (initialState, threadSafetyWasEnabled, afterMultiThread,
 *    thread1Operations, thread2Operations)
 */
std::tuple<bool, bool, bool, int, int> runMultiThreadAutoEnableScenario() {
    auto &manager = reaction::ThreadManager::getInstance();
    manager.resetForTesting();

    bool initialState = manager.isThreadSafetyEnabled();

    // Create shared variable
    auto sharedVar = reaction::var(0);

    std::atomic<int> thread1Operations{0};
    std::atomic<int> thread2Operations{0};

    std::atomic<bool> threadSafetyWasEnabled{false};

    // Thread 1
    std::thread thread1([&]() {
        for (int i = 0; i < 100; ++i) {
            sharedVar.value(i); // This triggers REACTION_REGISTER_THREAD
            thread1Operations++;
            if (i == 50) {
                // Check if thread safety was enabled by this point
                threadSafetyWasEnabled = manager.isThreadSafetyEnabled();
            }
            std::this_thread::sleep_for(std::chrono::microseconds(10));
        }
    });

    // Thread 2
    std::thread thread2([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Let thread1 start first
        for (int i = 0; i < 100; ++i) {
            int value = sharedVar.get(); // This triggers REACTION_REGISTER_THREAD
            (void)value;
            thread2Operations++;
            std::this_thread::sleep_for(std::chrono::microseconds(10));
        }
    });

    thread1.join();
    thread2.join();

    bool afterMultiThread = manager.isThreadSafetyEnabled();

    return {initialState,
            threadSafetyWasEnabled.load(),
            afterMultiThread,
            thread1Operations.load(),
            thread2Operations.load()};
}

