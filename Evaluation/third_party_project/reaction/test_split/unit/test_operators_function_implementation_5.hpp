

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <string>
#include <vector>

namespace operator_test_functions {

/**
 * @brief Encapsulates results of reactive notification operations.
 */
struct ReactiveNotificationsResult {
    int notification_count_after_creation;
    int notification_count_after_pre_increment;
    int value_after_pre_increment;
    int notification_count_after_plus_equal;
    int value_after_plus_equal;
    int notification_count_after_mul_equal;
    int value_after_mul_equal;
    int notification_count_after_post_increment;
    int value_after_post_increment;
    int post_increment_old_value;
};

/**
 * @brief Execute a sequence of operations that should trigger reactive notifications.
 *
 * @param initial Initial integer value.
 * @return ReactiveNotificationsResult Recorded notification counts and values.
 */
ReactiveNotificationsResult run_reactive_notifications_sequence(int initial) {
    ReactiveNotificationsResult result{};
    auto v = reaction::var(initial);
    int notification_count = 0;

    auto action = reaction::action([&notification_count, &v]() {
        notification_count++;
        std::cout << "Value changed to: " << v() << std::endl;
    });

    result.notification_count_after_creation = notification_count;

    ++v;
    result.notification_count_after_pre_increment = notification_count;
    result.value_after_pre_increment = v.get();

    v += 5;
    result.notification_count_after_plus_equal = notification_count;
    result.value_after_plus_equal = v.get();

    v *= 2;
    result.notification_count_after_mul_equal = notification_count;
    result.value_after_mul_equal = v.get();

    auto old_val = v++;
    result.notification_count_after_post_increment = notification_count;
    result.value_after_post_increment = v.get();
    result.post_increment_old_value = old_val;

    return result;
}

} // namespace operator_test_functions

