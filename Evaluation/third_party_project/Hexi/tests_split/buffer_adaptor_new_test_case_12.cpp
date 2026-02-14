

#include <gtest/gtest.h>

#include "buffer_adaptor_function_implementation_12.hpp"

TEST(buffer_adaptor, write_seek_start) {
  const auto out = buffer_adaptor_write_seek_start_outcome();
  ASSERT_EQ(out.buffer_size, 3);
  ASSERT_EQ(out.adaptor_size, out.buffer_size);
  ASSERT_TRUE(out.buffer_equals_values);
}

