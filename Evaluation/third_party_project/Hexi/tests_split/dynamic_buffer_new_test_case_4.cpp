
#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <gtest/gtest.h>
#include <tuple>

#include "dynamic_buffer_function_implementation_4.hpp"

TEST(dynamic_buffer, clear) {
  const int iterations = 100;

  const auto [size_before, size_after, is_empty, blocks] =
      dynamic_buffer_write_then_clear(iterations);

  ASSERT_EQ(sizeof(int) * iterations, size_before) << "Chain size is incorrect";
  ASSERT_EQ(0u, size_after) << "Chain size is incorrect";
  ASSERT_TRUE(is_empty);
  ASSERT_EQ(0u, blocks);
}
