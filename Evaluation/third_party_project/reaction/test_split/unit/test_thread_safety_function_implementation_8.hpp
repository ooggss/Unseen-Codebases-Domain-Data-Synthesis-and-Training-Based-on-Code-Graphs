

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

/**
 * Functional core for: ThreadSafetyTest.ResetInvalidationConcurrency
 *
 * @return tuple: (readCount, invalidationErrors,
 *                 finalVarValue, finalExprValue, finalDependentValue)
 */
std::tuple<int,int,int,int,int>
runResetInvalidationConcurrencyScenario() {
    auto &manager = reaction::ThreadManager::getInstance();
    manager.resetForTesting();

    std::atomic<bool> resetCompleted{false};
    std::atomic<int> readCount{0};
    std::atomic<int> invalidationErrors{0};

    auto sharedVar = reaction::var(10);
    auto sharedExpr = reaction::calc([&]() {
        return sharedVar() * 2;
    });
    auto dependentExpr = reaction::calc([&]() {
        return sharedExpr() * 3;
    });

    // Initial state check in caller via expectations, but execute here
    (void)sharedExpr.get();
    (void)dependentExpr.get();

    std::thread resetThread([&]() {
        sharedVar.value(20);

        (void)sharedExpr.get();
        (void)dependentExpr.get();

        sharedExpr.reset([&]() {
            return sharedVar.get() * 3;
        });

        (void)sharedExpr.get();
        (void)dependentExpr.get();
        resetCompleted = true;
    });

    std::thread readThread([&]() {
        while (!resetCompleted.load()) {
            int varValue = sharedVar.get();
            int exprValue = sharedExpr.get();
            int dependentValue = dependentExpr.get();

            if (varValue == 10 && exprValue != 20) {
                invalidationErrors++;
            } else if (varValue == 20 && exprValue != 60) {
                invalidationErrors++;
            } else if (varValue == 20 && exprValue == 60 && dependentValue != 180) {
                invalidationErrors++;
            }

            readCount++;
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }

        int finalVarValue = sharedVar.get();
        int finalExprValue = sharedExpr.get();
        int finalDependentValue = dependentExpr.get();

        if (finalVarValue == 20 && finalExprValue == 60 && finalDependentValue != 180) {
            invalidationErrors++;
        }
    });

    resetThread.join();
    readThread.join();

    int finalVarValue = sharedVar.get();
    int finalExprValue = sharedExpr.get();
    int finalDependentValue = dependentExpr.get();

    return {readCount.load(),
            invalidationErrors.load(),
            finalVarValue,
            finalExprValue,
            finalDependentValue};
}

