

#include <gtest/gtest.h>
#include <utility>

#include "buffer_adaptor_function_implementation_3.hpp"

TEST(buffer_adaptor, resize_match) {
  const auto [initial, after] = buffer_adaptor_resize_match_sizes();
  ASSERT_EQ(initial.first, initial.second);
  ASSERT_EQ(after.first, after.second);
}

