

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <atomic>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

/**
 * Functional core for: ThreadSafetyTest.SharedDependencyGraphReadOnly
 *
 * @return tuple:
 *   (initVal1, initVal2, initVal3,
 *    operationsCompleted, raceDetected, exceptionCount,
 *    finalVal1, finalVal2, finalVal3)
 */
std::tuple<int,int,int,int,bool,int,int,int,int>
runSharedDependencyGraphReadOnlyScenario() {
    auto &manager = reaction::ThreadManager::getInstance();
    manager.resetForTesting();

    std::atomic<int> operationsCompleted{0};
    std::atomic<bool> raceDetected{false};
    std::atomic<int> exceptionCount{0};

    auto sharedVar1 = reaction::var(42);
    auto sharedVar2 = reaction::var(24);

    auto sharedExpr1 = reaction::calc([&]() {
        return sharedVar1.get() + sharedVar2.get();
    });

    auto sharedExpr2 = reaction::calc([&]() {
        return sharedVar1.get() * sharedVar2.get();
    });

    auto sharedExpr3 = reaction::calc([&]() {
        return sharedExpr1.get() + sharedExpr2.get();
    });

    int initVal1 = sharedExpr1.get();
    int initVal2 = sharedExpr2.get();
    int initVal3 = sharedExpr3.get();

    const int EXPECTED_VAL1 = 42 + 24;                       // 66
    const int EXPECTED_VAL2 = 42 * 24;                       // 1008
    const int EXPECTED_VAL3 = EXPECTED_VAL1 + EXPECTED_VAL2; // 1074

    const int numThreads = 4;
    const int operationsPerThread = 1000;

    auto readOnlyOperation = [&](int) {
        try {
            for (int i = 0; i < operationsPerThread; ++i) {
                int val1 = sharedExpr1.get();
                int val2 = sharedExpr2.get();
                int val3 = sharedExpr3.get();

                if (val1 < 0 || val2 < 0 || val3 < 0) {
                    raceDetected = true;
                }

                if (val1 != EXPECTED_VAL1) {
                    raceDetected = true;
                }

                if (val2 != EXPECTED_VAL2) {
                    raceDetected = true;
                }

                if (std::abs(val3 - EXPECTED_VAL3) > 10) {
                    raceDetected = true;
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
        threads.emplace_back(readOnlyOperation, i);
    }
    for (auto &thread : threads) {
        thread.join();
    }

    int finalVal1 = sharedExpr1.get();
    int finalVal2 = sharedExpr2.get();
    int finalVal3 = sharedExpr3.get();

    return {initVal1, initVal2, initVal3,
            operationsCompleted.load(),
            raceDetected.load(),
            exceptionCount.load(),
            finalVal1, finalVal2, finalVal3};
}

