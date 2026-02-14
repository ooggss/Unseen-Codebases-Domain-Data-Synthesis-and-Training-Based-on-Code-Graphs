
#include <gtest/gtest.h>

#include <cstddef>
#include <tuple>

#include "static_buffer_function_implementation_15.hpp"

TEST(static_buffer, defragment) {
  const auto [free0, first_read, free1, free2, after_copy, buf0, ptr0, read_b, read_c, threw] =
      static_buffer_defragment_impl();

  ASSERT_EQ(free0, 0u);
  ASSERT_EQ(first_read, 'a');
  ASSERT_EQ(free1, 0u);
  ASSERT_EQ(free2, 1u);
  ASSERT_EQ(after_copy, 'b');
  ASSERT_EQ(buf0, 'b');
  ASSERT_EQ(ptr0, 'b');
  ASSERT_EQ(read_b, 'b');
  ASSERT_EQ(read_c, 'c');
  ASSERT_TRUE(threw);
}
