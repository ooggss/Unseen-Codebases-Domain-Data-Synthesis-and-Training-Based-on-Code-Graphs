
#include <gtest/gtest.h>

#include <utility>

#include "static_buffer_function_implementation_2.hpp"

TEST(static_buffer, empty) {
  const auto [before, after] = static_buffer_empty_after_write_impl();
  ASSERT_TRUE(before);
  ASSERT_FALSE(after);
}
