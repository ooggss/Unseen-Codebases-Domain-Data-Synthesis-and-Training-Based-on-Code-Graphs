
#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <ranges>
#include <utility>

#include "static_buffer_function_implementation_10.hpp"

TEST(static_buffer, write_seek_start) {
  const std::array<char, 3> values{'4', '5', '6'};
  const auto [size, out] = static_buffer_write_seek_start_impl();
  ASSERT_EQ(size, values.size());
  ASSERT_TRUE(std::ranges::equal(out, values));
}
