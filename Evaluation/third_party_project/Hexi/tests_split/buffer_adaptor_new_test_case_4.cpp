

#include <gtest/gtest.h>
#include <array>
#include <cstdint>

#include "buffer_adaptor_function_implementation_4.hpp"

TEST(buffer_adaptor, read_one) {
  const auto [remaining_size, value] = buffer_adaptor_read_one_result();
  ASSERT_EQ(remaining_size, (std::array<std::uint8_t, 3>{1,2,3}.size() - 1));
  ASSERT_EQ(value, 1);
}

