

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

/**
 * Functional core for: ThreadSafetyTest.VarIncrementConcurrency
 *
 * @return tuple: (finalValue, totalOperationsPerformed, threadsCompleted, raceDetected)
 */
std::tuple<int,int,int,bool>
runVarIncrementConcurrencyScenario() {
    auto &manager = reaction::ThreadManager::getInstance();
    manager.resetForTesting();

    auto sharedCounter = reaction::var(0);

    const int numThreads = 4;
    const int incrementsPerThread = 50;

    std::atomic<int> totalOperationsPerformed{0};
    std::atomic<int> threadsCompleted{0};
    std::atomic<bool> raceDetected{false};
    std::vector<std::thread> threads;

    auto incrementTask = [&](int) {
        try {
            for (int i = 0; i < incrementsPerThread; ++i) {
                ++sharedCounter;
                totalOperationsPerformed++;
            }
            threadsCompleted++;
        } catch (const std::exception &) {
            raceDetected = true;
        } catch (...) {
            raceDetected = true;
        }
    };

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(incrementTask, i);
    }
    for (auto &thread : threads) {
        thread.join();
    }

    int finalValue = sharedCounter.get();

    return {finalValue,
            totalOperationsPerformed.load(),
            threadsCompleted.load(),
            raceDetected.load()};
}

