
#include <gtest/gtest.h>

#include <cstddef>
#include <utility>

#include "static_buffer_function_implementation_0.hpp"

TEST(static_buffer, initial_empty) {
  const auto [is_empty, size] = static_buffer_initial_empty_impl();
  ASSERT_TRUE(is_empty);
  ASSERT_EQ(size, 0u);
}
