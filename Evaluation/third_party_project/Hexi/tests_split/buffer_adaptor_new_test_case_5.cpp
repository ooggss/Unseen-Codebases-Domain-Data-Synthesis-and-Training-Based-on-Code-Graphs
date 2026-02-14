

#include <gtest/gtest.h>
#include <ranges>
#include <array>

#include "buffer_adaptor_function_implementation_5.hpp"

TEST(buffer_adaptor, read_all) {
  const auto [buffer, values] = buffer_adaptor_read_all_values();
  ASSERT_TRUE(std::ranges::equal(buffer, values));
}

