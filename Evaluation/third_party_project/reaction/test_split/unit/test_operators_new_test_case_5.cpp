

#include <gtest/gtest.h>

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

#include "test_operators_function_implementation_5.hpp"

using namespace operator_test_functions;

/**
 * @brief Test that operators work with reactive notifications
 */
TEST(OperatorTest, ReactiveNotifications) {
    int initial = 0;

    auto result = run_reactive_notifications_sequence(initial);

    EXPECT_EQ(result.notification_count_after_creation, 1);

    EXPECT_EQ(result.notification_count_after_pre_increment, 2);
    EXPECT_EQ(result.value_after_pre_increment, 1);

    EXPECT_EQ(result.notification_count_after_plus_equal, 3);
    EXPECT_EQ(result.value_after_plus_equal, 6);

    EXPECT_EQ(result.notification_count_after_mul_equal, 4);
    EXPECT_EQ(result.value_after_mul_equal, 12);

    EXPECT_EQ(result.notification_count_after_post_increment, 5);
    EXPECT_EQ(result.value_after_post_increment, 13);
    EXPECT_EQ(result.post_increment_old_value, 12);

    std::cout << "✅ Reactive notifications test passed" << std::endl;
}

