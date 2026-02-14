
#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <gtest/gtest.h>
#include <utility>

#include "dynamic_buffer_function_implementation_3.hpp"

TEST(dynamic_buffer, skip) {
  const int foo = 960;
  const int bar = 296;

  const auto [out, remaining] = dynamic_buffer_skip_then_read(foo, bar);

  ASSERT_EQ(0u, remaining) << "Chain size is incorrect";
  ASSERT_EQ(bar, out) << "Skip produced incorrect result";
}
