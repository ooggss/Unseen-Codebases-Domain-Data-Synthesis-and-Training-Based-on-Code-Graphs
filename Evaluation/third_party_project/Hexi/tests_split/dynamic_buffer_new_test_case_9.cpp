
#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <gtest/gtest.h>
#include <tuple>

#include "dynamic_buffer_function_implementation_9.hpp"

TEST(dynamic_buffer, copy_chain) {
  const int foo = 5491;

  const auto [size_after_writes, chain2_before, chain_after_copy, chain2_after_copy,
              chain_after_read, out_from_chain2] =
      dynamic_buffer_copy_chain_independence(foo);

  ASSERT_EQ(sizeof(int) * 2, size_after_writes) << "Chain size is incorrect";
  ASSERT_EQ(0u, chain2_before) << "Chain size is incorrect";

  ASSERT_EQ(sizeof(int) * 2, chain_after_copy) << "Chain size is incorrect";
  ASSERT_EQ(sizeof(int) * 2, chain2_after_copy) << "Chain size is incorrect";

  ASSERT_EQ(sizeof(int), chain_after_read) << "Chain size is incorrect";
  ASSERT_EQ(foo, out_from_chain2) << "Chain output is incorrect";
}
