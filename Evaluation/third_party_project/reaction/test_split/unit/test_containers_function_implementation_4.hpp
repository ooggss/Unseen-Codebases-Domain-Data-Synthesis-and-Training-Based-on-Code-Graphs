

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

using namespace reaction;

/**
 * Function: create_react_unordered_map_and_update
 *
 * Creates a vector of Vars [0, N) and an unordered_map<Calc<int>, std::string>
 * where the key is a Calc depending on each Var, and the value is the index
 * as string. Then updates all Vars to i*2 and returns the resulting pair
 * (key_value, mapped_string) for each entry.
 *
 * @param N Number of elements.
 * @return std::vector<std::pair<int, std::string>> Each pair is
 *         {computed_key_value, stored_string}.
 */
std::vector<std::pair<int, std::string>>
create_react_unordered_map_and_update(int N) {
    std::vector<Var<int>> rc;
    rc.reserve(N);
    for (int i = 0; i < N; ++i) {
        rc.push_back(create(i));
    }

    std::unordered_map<Calc<int>, std::string> rc5;
    rc5.reserve(N);
    for (int i = 0; i < N; ++i) {
        rc5.emplace(create([i, &rc]() { return rc[i](); }), std::to_string(i));
    }

    for (int i = 0; i < N; ++i) {
        rc[i].value(i * 2);
    }

    std::vector<std::pair<int, std::string>> result;
    result.reserve(rc5.size());
    for (auto &[key, value] : rc5) {
        result.emplace_back(key.get(), value);
    }
    return result;
}

