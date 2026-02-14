
#include <gtest/gtest.h>

#include <cstddef>
#include <utility>

#include "static_buffer_function_implementation_5.hpp"

TEST(static_buffer, single_read_skip) {
  const auto [remaining, first] = static_buffer_single_read_skip_impl();
  ASSERT_EQ(remaining, 1u);
  ASSERT_EQ(first, '3');
}
