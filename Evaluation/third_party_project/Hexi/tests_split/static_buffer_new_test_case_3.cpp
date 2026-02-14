
#include <gtest/gtest.h>

#include <cstddef>
#include <utility>

#include "static_buffer_function_implementation_3.hpp"

TEST(static_buffer, read_one) {
  const auto [remaining, value] = static_buffer_read_one_impl();
  ASSERT_EQ(remaining, 2u);
  ASSERT_EQ(value, '1');
}
