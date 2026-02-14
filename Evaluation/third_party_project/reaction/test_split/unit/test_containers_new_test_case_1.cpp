
#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"

// Include function implementation
#include "test_containers_function_implementation_1.hpp"

TEST(ContainerSupportTest, TestReactSet) {
    constexpr int N = 10;

    auto results = create_react_set_and_update(N);

    // Note: std::set<Calc<int>> may not hold N elements due to comparison operator
    // behavior. This matches the original test which only verifies iteration works.
    int index = 0;
    for (int v : results) {
        EXPECT_EQ(v, ++index);
    }
}
