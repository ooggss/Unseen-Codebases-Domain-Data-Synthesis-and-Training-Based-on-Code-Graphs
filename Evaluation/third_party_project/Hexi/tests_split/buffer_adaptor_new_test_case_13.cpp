

#include <gtest/gtest.h>
#include <array>

#include "buffer_adaptor_function_implementation_13.hpp"

TEST(buffer_adaptor, read_ptr) {
  const auto observed = buffer_adaptor_read_ptr_sequence();
  ASSERT_EQ(observed[0], 1);
  ASSERT_EQ(observed[1], 2);
  ASSERT_EQ(observed[2], 3);
}

