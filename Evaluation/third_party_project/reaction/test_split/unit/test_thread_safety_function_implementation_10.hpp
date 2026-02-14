

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <atomic>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

/**
 * Functional core for: ThreadSafetyTest.ConcurrentReactiveOperations
 *
 * @return tuple: (operationsCompleted, raceDetected, someCalcsUpdated)
 */
std::tuple<int,bool,bool>
runConcurrentReactiveOperationsScenario() {
    auto &manager = reaction::ThreadManager::getInstance();
    manager.resetForTesting();

    constexpr int N = 10;

    std::vector<reaction::Var<int>> sharedVars(N);
    std::vector<reaction::Calc<int>> sharedCalcs(N);
    std::vector<reaction::Action<>> sharedActions(N);

    for (int i = 0; i < N; ++i) {
        sharedVars[i] = reaction::var(i);
        sharedCalcs[i] = reaction::calc([]() { return 1; });
        sharedActions[i] = reaction::action([]() {});
    }

    std::atomic<int> operationsCompleted{0};
    std::atomic<bool> raceDetected{false};
    std::vector<std::thread> threads1, threads2;

    auto calcResetTask = [&]() {
        try {
            std::mt19937 gen(std::random_device{}());
            std::uniform_int_distribution<> dist(0, N - 1);

            for (int i = 0; i < 5; ++i) {
                auto rd1 = dist(gen);
                auto rd2 = dist(gen);
                auto rd3 = dist(gen);

                sharedCalcs[rd1].reset([&, rd2, rd3]() {
                    return sharedVars[rd2]() + sharedVars[rd3]();
                });

                operationsCompleted++;
            }
        } catch (const std::exception &) {
            raceDetected = true;
        } catch (...) {
            raceDetected = true;
        }
    };

    auto actionResetTask = [&]() {
        try {
            std::mt19937 gen(std::random_device{}());
            std::uniform_int_distribution<> dist(0, N - 1);

            for (int i = 0; i < 5; ++i) {
                auto rd1 = dist(gen);
                auto rd2 = dist(gen);
                auto rd3 = dist(gen);

                sharedActions[rd1].reset([&, rd2, rd3]() {
                    int result = sharedCalcs[rd2]() + sharedCalcs[rd3]();
                    (void)result;
                });

                operationsCompleted++;
            }
        } catch (const std::exception &) {
            raceDetected = true;
        } catch (...) {
            raceDetected = true;
        }
    };

    const int numThreadsPerType = 5;

    for (int i = 0; i < numThreadsPerType; ++i) {
        threads1.emplace_back(calcResetTask);
        threads2.emplace_back(actionResetTask);
    }

    for (auto &t : threads1) t.join();
    for (auto &t : threads2) t.join();

    bool someCalcsUpdated = false;
    for (int i = 0; i < N; ++i) {
        try {
            int calcResult = sharedCalcs[i]();
            if (calcResult != 1) {
                someCalcsUpdated = true;
                break;
            }
        } catch (...) {
            // ignore in core, test can still assert
        }
    }

    return {operationsCompleted.load(), raceDetected.load(), someCalcsUpdated};
}

