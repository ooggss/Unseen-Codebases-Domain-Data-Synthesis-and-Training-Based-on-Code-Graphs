

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Include function implementation
#include "test_containers_function_implementation_2.hpp"

TEST(ContainerSupportTest, TestReactListActions) {
    constexpr int N = 10;

    auto final_values = create_react_list_actions_and_trigger(N);

    ASSERT_EQ(final_values.size(), static_cast<size_t>(N));
    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(final_values[i], i - 1);
    }
}

