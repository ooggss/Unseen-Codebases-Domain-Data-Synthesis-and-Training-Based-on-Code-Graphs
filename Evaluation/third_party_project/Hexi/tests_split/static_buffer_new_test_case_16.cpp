
#include <gtest/gtest.h>

#include <cstddef>
#include <tuple>

#include "static_buffer_function_implementation_16.hpp"

TEST(static_buffer, free_buff) {
  const auto [f0, f1, f2, f3, threw] = static_buffer_free_buff_impl();
  ASSERT_EQ(f0, 3u);
  ASSERT_EQ(f1, 2u);
  ASSERT_EQ(f2, 1u);
  ASSERT_EQ(f3, 0u);
  ASSERT_TRUE(threw);
}
