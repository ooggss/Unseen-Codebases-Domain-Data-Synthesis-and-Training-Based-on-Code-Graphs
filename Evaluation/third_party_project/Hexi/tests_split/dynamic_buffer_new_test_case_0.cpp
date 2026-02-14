
#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <gtest/gtest.h>
#include <cstddef>
#include <vector>

// In a real project, include via a header; provided inline for this split.
#include "dynamic_buffer_function_implementation_0.hpp"

TEST(dynamic_buffer, size) {
  const auto sizes = dynamic_buffer_size_sequence(
      /*reserve_amount=*/50,
      /*read_amount=*/20,
      /*skip_amount=*/10,
      /*write_amount=*/20);

  ASSERT_EQ(0u, sizes[0]) << "Chain size is incorrect";
  ASSERT_EQ(50u, sizes[1]) << "Chain size is incorrect";
  ASSERT_EQ(30u, sizes[2]) << "Chain size is incorrect";
  ASSERT_EQ(20u, sizes[3]) << "Chain size is incorrect";
  ASSERT_EQ(40u, sizes[4]) << "Chain size is incorrect";
  ASSERT_EQ(0u, sizes[5]) << "Chain size is incorrect";
}
