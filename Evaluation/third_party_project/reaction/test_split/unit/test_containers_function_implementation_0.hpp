

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

using namespace reaction;

/**
 * Function: create_react_vector_and_get_values
 *
 * Creates a vector of reactive Vars, initializes them with consecutive
 * integers [0, N), and returns their current values.
 *
 * @param N Number of elements to create.
 * @return std::vector<int> Values read from the reactive variables.
 */
std::vector<int> create_react_vector_and_get_values(int N) {
    std::vector<Var<int>> rc;
    rc.reserve(N);
    for (int i = 0; i < N; ++i) {
        rc.push_back(create(i));
    }

    std::vector<int> values;
    values.reserve(N);
    for (int i = 0; i < N; ++i) {
        values.push_back(rc[i].get());
    }
    return values;
}

