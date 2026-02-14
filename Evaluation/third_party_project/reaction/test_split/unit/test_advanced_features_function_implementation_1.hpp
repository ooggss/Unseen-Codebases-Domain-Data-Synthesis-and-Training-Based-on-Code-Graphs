

/*
 * Copyright (c) 2025 Lummy
 *
 * This software is released under the MIT License.
 * See the LICENSE file in the project root for full details.
 */

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

/**
 * Function: compute_reactive_person_name_string
 *
 * This function encapsulates the core logic of the original
 * `AdvancedFeaturesTest.TestField` test:
 * - create a Person and wrap it in a reactive variable `p`
 * - create a reactive variable `a`
 * - create a derived computation `ds` that concatenates `a` and `p.getName()`
 * - read the initial value, then mutate the person's name via `p->setName`
 *   and read the updated value
 *
 * @return std::pair<std::string, std::string>
 *         first  -> value of ds before changing the name
 *         second -> value of ds after changing the name
 */
std::pair<std::string, std::string> compute_reactive_person_name_string() {
    Person person{"lummy", 18};
    auto p = reaction::var(person);
    auto a = reaction::var(1);
    auto ds = reaction::calc(
        [](int aa, auto pp) {
            return std::to_string(aa) + pp.getName();
        },
        a, p);

    std::string before = ds.get();
    p->setName("lummy-new");
    std::string after = ds.get();

    return {before, after};
}

