
#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <tuple>
#include <vector>

#include "dynamic_buffer_function_implementation_1.hpp"

TEST(dynamic_buffer, read_write_consistency) {
  const char text[] = "The quick brown fox jumps over the lazy dog";
  const int num = 41521;

  const std::vector<char> text_bytes(text, text + sizeof(text)); // include '\0'
  const auto [num_out, text_out, remaining] =
      dynamic_buffer_read_write_roundtrip(text_bytes, num);

  ASSERT_EQ(num, num_out) << "Read produced incorrect result";
  ASSERT_STREQ(text, text_out.c_str()) << "Read produced incorrect result";
  ASSERT_EQ(0u, remaining) << "Chain should be empty";
}
