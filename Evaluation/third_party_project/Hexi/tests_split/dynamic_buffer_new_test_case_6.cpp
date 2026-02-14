
#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <gtest/gtest.h>
#include <string>
#include <tuple>

#include "dynamic_buffer_function_implementation_6.hpp"

TEST(dynamic_buffer, pop_front_push_back) {
  const std::string text("This is a string that is almost certainly longer than 32 bytes");
  const std::size_t expected_written = text.length(); // buffer->write writes up to provided length

  const auto [before, after_push, after_pop] = dynamic_buffer_push_back_then_pop_front(text);

  ASSERT_EQ(0u, before) << "Chain size is incorrect";
  ASSERT_EQ(expected_written, after_push) << "Chain size is incorrect";
  ASSERT_EQ(0u, after_pop) << "Chain size is incorrect";
}
