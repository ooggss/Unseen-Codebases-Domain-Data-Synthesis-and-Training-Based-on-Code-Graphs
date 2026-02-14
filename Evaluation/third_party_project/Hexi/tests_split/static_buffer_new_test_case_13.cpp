
#include <gtest/gtest.h>

#include <array>
#include <cstddef>

#include <hexi/static_buffer.h>

#include "static_buffer_function_implementation_13.hpp"

TEST(static_buffer, find_first_of) {
  const auto pos = static_buffer_find_first_of_impl();
  ASSERT_EQ(pos[0], (hexi::static_buffer<char, 64>::npos));
  ASSERT_EQ(pos[1], 43u);
  ASSERT_EQ(pos[2], 0u);
  ASSERT_EQ(pos[3], 32u);
}
