
#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <gtest/gtest.h>
#include <utility>

#include "dynamic_buffer_function_implementation_13.hpp"

TEST(dynamic_buffer, block_size) {
  const auto [bs1, bs2] = dynamic_buffer_report_block_sizes();
  ASSERT_EQ(bs1, 32u);
  ASSERT_EQ(bs2, 64u);
}
