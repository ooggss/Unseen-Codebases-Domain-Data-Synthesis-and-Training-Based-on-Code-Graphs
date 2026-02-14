#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

struct ConstVarResult {
    int initialSum;
    int updatedSum;
};

/**
 * Function: Demonstrate constVar feeding into calculations alongside mutable vars
 *
 * @param baseValue Mutable component value
 * @param constValue Constant component used via constVar
 * @param delta Increment applied to the mutable component
 * @return ConstVarResult Snapshot of calculation outputs before/after update
 */
ConstVarResult test_const_var_propagation(int baseValue, int constValue, int delta) {
    using namespace reaction;

    auto mutableVar = var(baseValue);
    auto immutableVar = constVar(constValue);

    auto sumCalc = calc([](int dynamicPart, int staticPart) {
        return dynamicPart + staticPart;
    }, mutableVar, immutableVar);

    const int initialSum = sumCalc.get();

    mutableVar.value(baseValue + delta);
    const int updatedSum = sumCalc.get();

    return ConstVarResult{
        .initialSum = initialSum,
        .updatedSum = updatedSum,
    };
}

}  // namespace test_reaction


