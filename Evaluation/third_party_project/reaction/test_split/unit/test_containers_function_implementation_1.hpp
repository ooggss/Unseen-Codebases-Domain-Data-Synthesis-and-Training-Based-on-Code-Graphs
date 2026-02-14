

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

using namespace reaction;

/**
 * Function: create_react_set_and_update
 *
 * Creates a vector of Vars [0, N) and a set of dependent Calcs that read
 * from those Vars. Then updates each Var to i+1 and returns the computed
 * values from the set in iteration order.
 *
 * Note: The iteration order of std::set<Calc<int>> must be consistent
 * with how Calc<int> defines comparison; the test will only verify that
 * the produced sequence is {1, 2, ..., N}.
 *
 * @param N Number of elements.
 * @return std::vector<int> Values of the Calcs after update.
 */
std::vector<int> create_react_set_and_update(int N) {
    std::vector<Var<int>> rc;
    rc.reserve(N);
    for (int i = 0; i < N; ++i) {
        rc.push_back(create(i));
    }

    std::set<Calc<int>> rc2;
    for (int i = 0; i < N; ++i) {
        rc2.insert(create([i, &rc]() { return rc[i](); }));
    }

    for (int i = 0; i < N; ++i) {
        rc[i].value(i + 1);
    }

    std::vector<int> results;
    results.reserve(N);
    for (auto &r : rc2) {
        results.push_back(r.get());
    }
    return results;
}

