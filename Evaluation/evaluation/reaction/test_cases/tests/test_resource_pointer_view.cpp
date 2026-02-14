#include <gtest/gtest.h>

#include "test_resource_pointer_view.hpp"

namespace test_reaction {

/**
 * Test Case: Ensure Resource::getRawPtr exposes a stable pointer that can mutate the value.
 *
 * Test Scenario:
 * - Construct Resource<int> with an initial value
 * - Retrieve raw pointer, modify value directly, and confirm the resource reflects the change
 * - Verify pointer identity remains stable across successive calls
 */
TEST(reaction, test_resource_pointer_view) {
  const int initialValue = 42;
  const int directWriteValue = 99;

  const auto snapshot = test_resource_pointer_view(initialValue, directWriteValue);

  EXPECT_EQ(snapshot.initialPointerValue, initialValue);
  EXPECT_EQ(snapshot.pointerValueAfterWrite, directWriteValue);
  EXPECT_TRUE(snapshot.pointerStable);
}

}  // namespace test_reaction

