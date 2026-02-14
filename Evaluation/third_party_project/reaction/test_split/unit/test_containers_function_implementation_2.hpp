

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

using namespace reaction;

/**
 * Function: create_react_list_actions_and_trigger
 *
 * Creates a vector of Vars [0, N) and a list of Actions that, when triggered,
 * print the current value of each Var. Then updates each Var to i-1 and
 * triggers all actions.
 *
 * This function is mainly for side-effect verification (stdout); it returns
 * the final values of the Vars so that tests can assert on them if needed.
 *
 * @param N Number of elements.
 * @return std::vector<int> Final values of Vars after update.
 */
std::vector<int> create_react_list_actions_and_trigger(int N) {
    std::vector<Var<int>> rc;
    rc.reserve(N);
    for (int i = 0; i < N; ++i) {
        rc.push_back(create(i));
    }

    std::list<Action<>> rc3;
    for (int i = 0; i < N; ++i) {
        rc3.push_back(create([i, &rc]() {
            std::cout << " rc " << i << " changed to " << rc[i]() << '\n';
        }));
    }

    for (int i = 0; i < N; ++i) {
        rc[i].value(i - 1);
    }

    // Trigger all actions so that any observers are notified / side effects occur
    for (auto &act : rc3) {
        act();
    }

    std::vector<int> final_values;
    final_values.reserve(N);
    for (int i = 0; i < N; ++i) {
        final_values.push_back(rc[i].get());
    }
    return final_values;
}

