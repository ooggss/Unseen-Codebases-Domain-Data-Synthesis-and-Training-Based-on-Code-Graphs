
#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

#include "dynamic_buffer_function_implementation_2.hpp"

TEST(dynamic_buffer, reserve_fetch_consistency) {
  const char text[] = "The quick brown fox jumps over the lazy dog";
  const std::vector<char> text_bytes(text, text + sizeof(text)); // include '\0'

  const auto [output, remaining] = dynamic_buffer_reserve_fetch_roundtrip(text_bytes);

  ASSERT_EQ(0u, remaining) << "Chain size is incorrect";
  ASSERT_STREQ(text, output.c_str()) << "Read produced incorrect result";
}
