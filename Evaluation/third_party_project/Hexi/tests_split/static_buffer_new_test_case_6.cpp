
#include <gtest/gtest.h>

#include <utility>

#include "static_buffer_function_implementation_6.hpp"

TEST(static_buffer, multiskip_read) {
  const auto [is_empty, value] = static_buffer_multiskip_read_impl();
  ASSERT_TRUE(is_empty);
  ASSERT_EQ(value, '6');
}
