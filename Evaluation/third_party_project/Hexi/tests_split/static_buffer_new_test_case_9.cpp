
#include <gtest/gtest.h>

#include <array>
#include <ranges>

#include "static_buffer_function_implementation_9.hpp"

TEST(static_buffer, write_seek_back) {
  const std::array<char, 3> expected{'1', '5', '6'};
  const auto actual = static_buffer_write_seek_back_impl();
  ASSERT_TRUE(std::ranges::equal(expected, actual));
}
