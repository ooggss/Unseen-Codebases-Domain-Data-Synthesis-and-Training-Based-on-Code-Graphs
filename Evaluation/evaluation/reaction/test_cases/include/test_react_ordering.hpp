#pragma once

#include <reaction/reaction.h>
#include <set>
#include <string>
#include <vector>

namespace test_reaction {

struct OrderingSnapshot {
    std::vector<std::string> orderedNames;
    bool allUnique;
};

/**
 * Function: Demonstrate React::operator< for ordering reactive handles.
 *
 * @param firstName Name assigned to the first reactive node
 * @param secondName Name assigned to the second reactive node
 * @param thirdName Name assigned to the third reactive node
 * @return OrderingSnapshot Snapshot of sorted names and uniqueness flag
 */
inline OrderingSnapshot test_react_ordering(const std::string &firstName,
                                            const std::string &secondName,
                                            const std::string &thirdName) {
    using namespace reaction;

    auto first = var(1).setName(firstName);
    auto second = var(2).setName(secondName);
    auto third = var(3).setName(thirdName);

    std::set<React<VarExpr, int, KeepHandle, ChangeTrig>> ordered;
    ordered.insert(first);
    ordered.insert(second);
    ordered.insert(third);

    std::vector<std::string> names;
    names.reserve(ordered.size());
    for (const auto &react : ordered) {
        names.push_back(react.getName());
    }

    bool unique = names.size() == 3;

    return OrderingSnapshot{
        .orderedNames = names,
        .allUnique = unique,
    };
}

}  // namespace test_reaction

