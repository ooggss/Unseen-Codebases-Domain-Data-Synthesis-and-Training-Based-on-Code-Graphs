#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Include function implementation (normally via header)
#include "test_containers_function_implementation_0.hpp"

TEST(ContainerSupportTest, TestReactVector) {
    constexpr int N = 10;

    // Call function under test
    auto values = create_react_vector_and_get_values(N);

    // Assertions
    ASSERT_EQ(values.size(), static_cast<size_t>(N));
    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(values[i], i);
    }
}
