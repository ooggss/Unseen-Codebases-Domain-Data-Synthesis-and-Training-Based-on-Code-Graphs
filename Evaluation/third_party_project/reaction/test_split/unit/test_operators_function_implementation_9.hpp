

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <chrono>
#include <string>
#include <vector>

namespace operator_test_functions {

/**
 * @brief Encapsulates results for performance test operations.
 */
struct PerformanceTestResult {
    int final_value;
    std::chrono::microseconds duration;
};

/**
 * @brief Execute a performance test with many operator applications.
 *
 * @param iterations Number of loop iterations.
 * @param increment_interval Interval at which an extra pre-increment is performed.
 * @return PerformanceTestResult Final value and elapsed time.
 */
PerformanceTestResult run_performance_test(int iterations, int increment_interval) {
    PerformanceTestResult result{};
    auto v = reaction::var(0);
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        v += 1;
        if (i % increment_interval == 0) {
            ++v;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    result.duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    result.final_value = v.get();

    return result;
}

} // namespace operator_test_functions

