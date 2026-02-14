

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

/**
 * Functional core for: ThreadSafetyTest.SharedDependencyGraphConcurrency
 *
 * @return tuple: (operationsCompleted, raceDetected, exceptionCount)
 */
std::tuple<int, bool, int>
runSharedDependencyGraphConcurrencyScenario() {
    auto &manager = reaction::ThreadManager::getInstance();
    manager.resetForTesting();

    std::atomic<int> operationsCompleted{0};
    std::atomic<bool> raceDetected{false};
    std::atomic<int> exceptionCount{0};

    // Create SHARED variables that will be accessed by multiple threads
    auto sharedVar1 = reaction::var(0);
    auto sharedVar2 = reaction::var(0);
    auto sharedVar3 = reaction::var(0);

    // Create SHARED expressions that depend on shared variables
    auto sharedExpr1 = reaction::calc([&]() {
        return sharedVar1() + sharedVar2();
    });

    auto sharedExpr2 = reaction::calc([&]() {
        return sharedVar2() * sharedVar3();
    });

    auto sharedExpr3 = reaction::calc([&]() {
        return sharedExpr1() + sharedExpr2();
    });

    const int numThreads = 3;
    const int operationsPerThread = 100;

    auto sharedOperation = [&](int) {
        try {
            for (int i = 0; i < operationsPerThread; ++i) {
                switch (i % 5) {
                case 0: {
                    int current = sharedVar1();
                    sharedVar1.value(current + 1);
                    break;
                }
                case 1: {
                    int current = sharedVar2();
                    sharedVar2.value(current - 1);
                    break;
                }
                case 2: {
                    (void)sharedExpr1();
                    (void)sharedExpr2();
                    (void)sharedExpr3();
                    break;
                }
                case 3: {
                    sharedExpr1.reset([&]() {
                        return sharedVar1() * sharedVar2();
                    });
                    break;
                }
                case 4: {
                    sharedExpr2.reset([&]() {
                        return sharedVar2() + sharedVar3();
                    });
                    break;
                }
                }
                operationsCompleted++;
            }
        } catch (const std::exception &) {
            exceptionCount++;
            raceDetected = true;
        } catch (...) {
            exceptionCount++;
            raceDetected = true;
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(sharedOperation, i);
    }
    for (auto &thread : threads) {
        thread.join();
    }

    return {operationsCompleted.load(),
            raceDetected.load(),
            exceptionCount.load()};
}

