

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Include function implementation
#include "test_containers_function_implementation_4.hpp"

TEST(ContainerSupportTest, TestReactUnorderedMap) {
    constexpr int N = 10;

    auto result = create_react_unordered_map_and_update(N);

    ASSERT_EQ(result.size(), static_cast<size_t>(N));
    for (const auto &pair : result) {
        int key_value = pair.first;
        int index = std::stoi(pair.second);
        EXPECT_EQ(key_value, index * 2);
    }
}

