

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <atomic>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

/**
 * Functional core for: ThreadSafetyTest.ConcurrentRandomReset
 *
 * @return tuple:
 *   (calcResetOperations, actionResetOperations,
 *    exceptionCaught, raceConditionDetected, threadSafetyEnabled,
 *    testVar0Value, testCalc1Value)
 */
std::tuple<int,int,bool,bool,bool,int,int>
runConcurrentRandomResetScenario() {
    auto &manager = reaction::ThreadManager::getInstance();
    manager.resetForTesting();

    constexpr int N = 50;
    constexpr int NUM_OPERATIONS_PER_THREAD = 10;

    std::vector<reaction::Var<int>> testVars(N);
    std::vector<reaction::Calc<int>> testCalcs(N);
    std::vector<reaction::Action<>> testActions(N);

    for (int i = 0; i < N; ++i) {
        testVars[i] = reaction::var(i);
        testCalcs[i] = reaction::calc([]() { return 1; });
        testActions[i] = reaction::action([]() {});
    }

    std::atomic<int> calcResetOperations{0};
    std::atomic<int> actionResetOperations{0};
    std::atomic<bool> exceptionCaught{false};
    std::atomic<bool> raceConditionDetected{false};

    auto calcResetTest = [&]() {
        try {
            thread_local std::mt19937 gen(std::random_device{}());
            thread_local std::uniform_int_distribution<> dist(0, N - 1);

            for (int op = 0; op < NUM_OPERATIONS_PER_THREAD; ++op) {
                auto rd1 = dist(gen);
                auto rd2 = dist(gen);
                auto rd3 = dist(gen);

                testCalcs[rd1].reset([&testVars, rd2, rd3]() -> int {
                    try {
                        return testVars[rd2]() + testVars[rd3]();
                    } catch (...) {
                        return 0;
                    }
                });

                calcResetOperations.fetch_add(1, std::memory_order_relaxed);
                std::this_thread::yield();
            }
        } catch (const std::exception &) {
            exceptionCaught.store(true, std::memory_order_relaxed);
        } catch (...) {
            exceptionCaught.store(true, std::memory_order_relaxed);
        }
    };

    auto actionResetTest = [&]() {
        try {
            thread_local std::mt19937 gen(std::random_device{}());
            thread_local std::uniform_int_distribution<> dist(0, N - 1);

            for (int op = 0; op < NUM_OPERATIONS_PER_THREAD; ++op) {
                auto rd1 = dist(gen);
                auto rd2 = dist(gen);
                auto rd3 = dist(gen);

                testActions[rd1].reset([&testCalcs, rd2, rd3]() {
                    try {
                        volatile int result = testCalcs[rd2]() + testCalcs[rd3]();
                        (void)result;
                    } catch (...) {
                    }
                });

                actionResetOperations.fetch_add(1, std::memory_order_relaxed);
                std::this_thread::yield();
            }
        } catch (const std::exception &) {
            exceptionCaught.store(true, std::memory_order_relaxed);
        } catch (...) {
            exceptionCaught.store(true, std::memory_order_relaxed);
        }
    };

    std::vector<std::thread> calcThreads, actionThreads;
    calcThreads.reserve(N);
    actionThreads.reserve(N);

    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        calcThreads.emplace_back(calcResetTest);
    }
    for (int i = 0; i < N; ++i) {
        actionThreads.emplace_back(actionResetTest);
    }

    for (auto &t : calcThreads) t.join();
    for (auto &t : actionThreads) t.join();

    auto endTime = std::chrono::high_resolution_clock::now();
    (void)startTime;
    (void)endTime;

    bool threadSafetyEnabled = manager.isThreadSafetyEnabled();

    int testValue1 = 0;
    int testValue2 = 0;
    try {
        testValue1 = testVars[0]();
        testValue2 = testCalcs[1]();
    } catch (...) {
        exceptionCaught.store(true, std::memory_order_relaxed);
    }

    return {calcResetOperations.load(),
            actionResetOperations.load(),
            exceptionCaught.load(),
            raceConditionDetected.load(),
            threadSafetyEnabled,
            testValue1,
            testValue2};
}

