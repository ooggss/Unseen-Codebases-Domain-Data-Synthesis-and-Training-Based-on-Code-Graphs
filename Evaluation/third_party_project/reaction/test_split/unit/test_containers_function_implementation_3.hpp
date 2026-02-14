

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

using namespace reaction;

/**
 * Function: create_react_map_and_update
 *
 * Creates a vector of Vars [0, N) and a map<int, Calc<std::string>> that
 * computes a string representation of each Var. Then updates each Var to i+1
 * and returns the map's computed values.
 *
 * @param N Number of elements.
 * @return std::map<int, std::string> Map from index to stringified value.
 */
std::map<int, std::string> create_react_map_and_update(int N) {
    std::vector<Var<int>> rc;
    rc.reserve(N);
    for (int i = 0; i < N; ++i) {
        rc.push_back(create(i));
    }

    std::map<int, Calc<std::string>> rc4;
    for (int i = 0; i < N; ++i) {
        rc4.insert({i, create([i, &rc]() { return std::to_string(rc[i]()); })});
    }

    for (int i = 0; i < N; ++i) {
        rc[i].value(i + 1);
    }

    std::map<int, std::string> result;
    for (int i = 0; i < N; ++i) {
        result[i] = rc4[i].get();
    }
    return result;
}

