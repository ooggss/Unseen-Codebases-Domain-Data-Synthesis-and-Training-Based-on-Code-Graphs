

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <chrono>

#include "test_operators_function_implementation_9.hpp"

using namespace operator_test_functions;

/**
 * @brief Performance test for operators
 */
TEST(OperatorTest, PerformanceTest) {
    int iterations = 10000;
    int increment_interval = 100;

    auto result = run_performance_test(iterations, increment_interval);

    EXPECT_EQ(result.final_value, 10000 + 100);

    std::cout << "✅ Performance test completed in " << result.duration.count() << " microseconds" << std::endl;
    std::cout << "Final value: " << result.final_value << std::endl;
}

