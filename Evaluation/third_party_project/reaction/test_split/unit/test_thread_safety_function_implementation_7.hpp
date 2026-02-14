

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <iostream>

/**
 * Functional core for: ThreadSafetyTest.ResetInvalidationBasic
 *
 * @return tuple: (expr1_initial, expr2_initial, expr3_initial,
 *                 expr1_after_reset1, expr2_after_reset1, expr3_after_reset1,
 *                 expr1_after_reset2, expr2_after_reset2, expr3_after_reset2)
 */
std::tuple<int,int,int,int,int,int,int,int,int>
runResetInvalidationBasicScenario() {
    auto &manager = reaction::ThreadManager::getInstance();
    manager.resetForTesting();

    auto var1 = reaction::var(10);
    auto var2 = reaction::var(20);

    auto expr1 = reaction::calc([&]() {
        return var1() * 2;
    });

    auto expr2 = reaction::calc([&]() {
        return var2() * 3;
    });

    auto expr3 = reaction::calc([&]() {
        return expr1() + expr2();
    });

    int expr1_initial = expr1.get(); // 20
    int expr2_initial = expr2.get(); // 60
    int expr3_initial = expr3.get(); // 80

    expr1.reset([&]() {
        return var1.get() * 5; // Changed from *2 to *5
    });

    int expr1_after_reset1 = expr1.get();  // 50
    int expr2_after_reset1 = expr2.get();  // 60
    int expr3_after_reset1 = expr3.get();  // 110

    expr2.reset([&]() {
        return var2.get() * 2; // Changed from *3 to *2
    });

    int expr1_after_reset2 = expr1.get(); // 50
    int expr2_after_reset2 = expr2.get(); // 40
    int expr3_after_reset2 = expr3.get(); // 90

    return {expr1_initial, expr2_initial, expr3_initial,
            expr1_after_reset1, expr2_after_reset1, expr3_after_reset1,
            expr1_after_reset2, expr2_after_reset2, expr3_after_reset2};
}

