
#define HEXI_BUFFER_DEBUG
#include <hexi/dynamic_buffer.h>
#include <hexi/buffer_sequence.h>
#undef HEXI_BUFFER_DEBUG

#include <gtest/gtest.h>
#include <tuple>

#include "dynamic_buffer_function_implementation_12.hpp"

TEST(dynamic_buffer, empty) {
  const auto value = 0;
  const auto [before, after] = dynamic_buffer_empty_before_after_write(value);

  ASSERT_TRUE(before);
  ASSERT_FALSE(after);
}
