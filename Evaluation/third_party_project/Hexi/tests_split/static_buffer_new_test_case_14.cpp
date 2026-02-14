
#include <gtest/gtest.h>

#include <utility>

#include "static_buffer_function_implementation_14.hpp"

TEST(static_buffer, advance_write) {
  const auto [b1, val] = static_buffer_advance_write_impl();
  ASSERT_EQ(b1, val);
}
