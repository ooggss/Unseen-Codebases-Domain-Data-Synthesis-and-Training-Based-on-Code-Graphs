#include <gtest/gtest.h>

#include "test_last_handle_restore.hpp"

namespace test_reaction {

/**
 * Test Case: Ensure LastHandle retains the last computed value after the source closes.
 */
TEST(reaction, test_last_handle_restore) {
  const int initialValue = 4;
  const int updatedValue = 11;

  const auto snapshot = test_last_handle_restore(initialValue, updatedValue);

  EXPECT_EQ(snapshot.initialValue, initialValue * 2);
  EXPECT_EQ(snapshot.afterUpdate, updatedValue * 2);
  EXPECT_EQ(snapshot.afterSourceClose, snapshot.afterUpdate);
}

}  // namespace test_reaction


