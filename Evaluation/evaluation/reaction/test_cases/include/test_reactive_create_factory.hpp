#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

struct CreateFactoryResult {
    int initialExpressionValue;
    int updatedExpressionValue;
    int squaredValueAfterUpdate;
};

/**
 * Function: Demonstrate create() overloads for var/expr/calc
 *
 * @param baseValue Initial value passed to create()
 * @param increment Amount added to the underlying reactive var
 * @return CreateFactoryResult Snapshot of expression/calc outputs
 */
CreateFactoryResult test_reactive_create_factory(int baseValue, int increment) {
    using namespace reaction;

    // create(value) -> reactive variable
    auto dynamicVar = create(baseValue);

    // create(expression) -> reactive expression built from operator syntax
    auto dynamicExpr = create((dynamicVar + 2) * 3);

    // create(fun, args...) -> reactive calculation bound to existing reactives
    auto dynamicCalc = create([](int value) {
        return value * value;
    }, dynamicVar);

    const int initialExpr = dynamicExpr.get();

    dynamicVar.value(baseValue + increment);

    const int updatedExpr = dynamicExpr.get();
    const int squared = dynamicCalc.get();

    return CreateFactoryResult{
        .initialExpressionValue = initialExpr,
        .updatedExpressionValue = updatedExpr,
        .squaredValueAfterUpdate = squared,
    };
}

}  // namespace test_reaction


