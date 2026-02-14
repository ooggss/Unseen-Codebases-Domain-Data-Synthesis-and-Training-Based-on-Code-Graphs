

#include <gtest/gtest.h>

#include "buffer_adaptor_function_implementation_9.hpp"

TEST(buffer_adaptor, write_append) {
  const auto out = buffer_adaptor_write_append_outcome();
  ASSERT_EQ(out.buffer_size, 6);
  ASSERT_EQ(out.adaptor_size, out.buffer_size);
  ASSERT_TRUE(out.buffer_equals_expected);
}

