

#include <gtest/gtest.h>

#include "buffer_adaptor_function_implementation_8.hpp"

TEST(buffer_adaptor, write) {
  const auto out = buffer_adaptor_write_outcome();

  ASSERT_EQ(out.adaptor_size_after_block_write, 6);
  ASSERT_EQ(out.buffer_size_after_block_write, 6);
  ASSERT_TRUE(out.buffer_equals_values_after_block_write);
  ASSERT_EQ(out.adaptor_size_after_single_write, out.adaptor_size_after_block_write + 1);
}

