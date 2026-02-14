
#include <gtest/gtest.h>

#include <array>

#include "static_buffer_function_implementation_12.hpp"

TEST(static_buffer, subscript) {
  const auto out = static_buffer_subscript_impl();
  ASSERT_EQ(out[0], '1');
  ASSERT_EQ(out[1], '2');
  ASSERT_EQ(out[2], '3');
  ASSERT_EQ(out[3], '4');
  ASSERT_EQ(out[4], '5');
  ASSERT_EQ(out[5], out[5]);
}
