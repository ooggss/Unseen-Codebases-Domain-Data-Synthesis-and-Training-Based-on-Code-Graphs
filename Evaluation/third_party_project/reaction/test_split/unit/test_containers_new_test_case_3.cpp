

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Include function implementation
#include "test_containers_function_implementation_3.hpp"

TEST(ContainerSupportTest, TestReactMap) {
    constexpr int N = 10;

    auto result = create_react_map_and_update(N);

    ASSERT_EQ(result.size(), static_cast<size_t>(N));
    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(result[i], std::to_string(i + 1));
    }
}

