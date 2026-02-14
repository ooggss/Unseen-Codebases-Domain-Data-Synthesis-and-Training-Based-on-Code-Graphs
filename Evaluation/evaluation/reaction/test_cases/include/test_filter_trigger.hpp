#pragma once

#include <reaction/reaction.h>
#include <cmath>
#include <string>
#include <tuple>

namespace test_reaction {

// ============================================
// Function implementations
// ============================================

/**
 * Function: Test filter trigger with conditional recomputation
 *
 * @param initialValue Initial sensor value
 * @param firstUpdate First update (expected to be within threshold)
 * @param secondUpdate Second update (expected to exceed threshold)
 * @param diffThreshold Minimum delta to trigger recomputation
 * @param levelThreshold Threshold to categorize HIGH vs NORMAL
 * @return std::tuple<std::string, int, int>
 *         {final status string, recompute count after first update, recompute count after second update}
 */
std::tuple<std::string, int, int> test_filter_trigger(double initialValue,
                                                      double firstUpdate,
                                                      double secondUpdate,
                                                      double diffThreshold,
                                                      double levelThreshold) {
    using namespace reaction;

    auto sensor = var(initialValue);

    int recomputeCount = 0;
    double lastProcessed = initialValue;

    auto statusCalc = calc<FilterTrig>([&](double value) {
        ++recomputeCount;
        lastProcessed = value;
        return value >= levelThreshold ? std::string("HIGH") : std::string("NORMAL");
    }, sensor);

    statusCalc.filter([&]() {
        return std::abs(sensor() - lastProcessed) > diffThreshold;
    });

    // Initial calculation runs once upon creation
    sensor.value(firstUpdate);
    const int countAfterFirst = recomputeCount;

    sensor.value(secondUpdate);
    const int countAfterSecond = recomputeCount;

    const std::string finalStatus = statusCalc.get();
    return {finalStatus, countAfterFirst, countAfterSecond};
}

}  // namespace test_reaction

