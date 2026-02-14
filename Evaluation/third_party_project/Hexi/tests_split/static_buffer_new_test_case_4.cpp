
#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <ranges>

#include "static_buffer_function_implementation_4.hpp"

TEST(static_buffer, read_all) {
  const std::array<char, 3> expected{'1', '2', '3'};
  const auto values = static_buffer_read_all_impl();
  ASSERT_TRUE(std::ranges::equal(values, expected));
}
