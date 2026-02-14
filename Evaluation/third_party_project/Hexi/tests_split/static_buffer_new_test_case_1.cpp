
#include <gtest/gtest.h>

#include <cstddef>
#include <tuple>

#include "static_buffer_function_implementation_1.hpp"

TEST(static_buffer, initial_not_empty) {
  const auto [is_empty, size, c0, c1] = static_buffer_initial_not_empty_impl();
  ASSERT_FALSE(is_empty);
  ASSERT_EQ(size, 2u);
  ASSERT_EQ(c0, '1');
  ASSERT_EQ(c1, '2');
}
