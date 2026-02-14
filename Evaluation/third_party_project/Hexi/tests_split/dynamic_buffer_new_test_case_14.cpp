
#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <gtest/gtest.h>
#include <cstdint>
#include <vector>

#include "dynamic_buffer_function_implementation_14.hpp"

TEST(dynamic_buffer, block_count) {
  const std::uint8_t value = 0;
  const auto counts = dynamic_buffer_block_count_sequence(value);

  ASSERT_EQ(counts[0], 1u);
  ASSERT_EQ(counts[1], 2u);
  ASSERT_EQ(counts[2], 4u);
  ASSERT_EQ(counts[3], 3u);
}
