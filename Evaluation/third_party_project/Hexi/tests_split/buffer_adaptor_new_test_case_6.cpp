

#include <gtest/gtest.h>
#include <array>

#include "buffer_adaptor_function_implementation_6.hpp"

TEST(buffer_adaptor, single_skip_read) {
  const auto [remaining, value] = buffer_adaptor_single_skip_then_read();
  ASSERT_EQ(remaining, 1);
  ASSERT_EQ(value, (std::array<std::uint8_t, 3>{1,2,3}[1]));
}

