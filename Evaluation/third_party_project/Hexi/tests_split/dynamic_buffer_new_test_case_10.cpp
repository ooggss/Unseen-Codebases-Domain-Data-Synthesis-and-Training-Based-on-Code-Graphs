
#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <gtest/gtest.h>
#include <tuple>

#include "dynamic_buffer_function_implementation_10.hpp"

TEST(dynamic_buffer, move_chain) {
  const int foo = 23113;

  const auto [source_after_write, dest_before, dest_after, out] =
      dynamic_buffer_move_chain_roundtrip(foo);

  ASSERT_EQ(sizeof(int), source_after_write) << "Chain size is incorrect";
  ASSERT_EQ(0u, dest_before) << "Chain size is incorrect";
  ASSERT_EQ(sizeof(int), dest_after) << "Chain size is incorrect";
  ASSERT_EQ(foo, out) << "Chain output is incorrect";
}
