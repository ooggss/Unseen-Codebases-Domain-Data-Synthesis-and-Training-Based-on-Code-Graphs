
#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <gtest/gtest.h>
#include <tuple>

#include "dynamic_buffer_function_implementation_8.hpp"

TEST(dynamic_buffer, copy) {
  const int foo = 54543;

  const auto [output, size_after_write, size_after_copy] =
      dynamic_buffer_copy_does_not_consume(foo);

  ASSERT_EQ(sizeof(int), size_after_write);
  ASSERT_EQ(sizeof(int), size_after_copy) << "Chain size is incorrect";
  ASSERT_EQ(foo, output) << "Copy output is incorrect";
}
