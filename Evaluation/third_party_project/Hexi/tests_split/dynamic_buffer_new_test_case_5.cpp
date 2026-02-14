
#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <tuple>

#include "dynamic_buffer_function_implementation_5.hpp"

TEST(dynamic_buffer, attach_tail) {
  const std::string text("This is a string that is almost certainly longer than 32 bytes");

  const auto [written, output, remaining] = dynamic_buffer_attach_tail_roundtrip(text);

  ASSERT_EQ(0u, remaining) << "Chain size is incorrect";
  ASSERT_EQ(0, std::memcmp(text.data(), output.data(), written)) << "Output is incorrect";
}
