
#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <gtest/gtest.h>
#include <string>
#include <utility>

#include "dynamic_buffer_function_implementation_7.hpp"

TEST(dynamic_buffer, retrieve_tail) {
  const std::string text("This string is < 32 bytes");

  const auto [has_tail, cmp] = dynamic_buffer_retrieve_tail_compare(text);

  ASSERT_TRUE(has_tail);
  ASSERT_EQ(0, cmp) << "Tail data is incorrect";
}
