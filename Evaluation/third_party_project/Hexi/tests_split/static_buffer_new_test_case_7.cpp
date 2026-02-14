
#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <ranges>
#include <utility>

#include "static_buffer_function_implementation_7.hpp"

TEST(static_buffer, write) {
  const std::array<std::uint8_t, 6> expected{1, 2, 3, 4, 5, 6};
  const auto [size, out] = static_buffer_write_impl();
  ASSERT_EQ(size, expected.size());
  ASSERT_TRUE(std::ranges::equal(expected, out));
}
