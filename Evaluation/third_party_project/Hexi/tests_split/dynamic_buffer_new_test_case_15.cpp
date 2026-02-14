
#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <gtest/gtest.h>
#include <string_view>
#include <tuple>

using namespace std::literals;

#include "dynamic_buffer_function_implementation_15.hpp"

TEST(dynamic_buffer, find_first_of) {
  const auto str = "The quick brown fox jumped over the lazy dog"sv;

  const auto [p0, p1, p2, p3] = dynamic_buffer_find_first_of_positions(
      str, std::byte('\0'), std::byte('g'), std::byte('T'), std::byte('t'));

  // direct string write is not terminated
  ASSERT_EQ(p0, hexi::dynamic_buffer<64>::npos);

  ASSERT_EQ(p1, 43u);
  ASSERT_EQ(p2, 0u);
  ASSERT_EQ(p3, 32u);
}
