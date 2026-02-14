

#include <gtest/gtest.h>
#include <array>

#include "buffer_adaptor_function_implementation_7.hpp"

TEST(buffer_adaptor, multiskip_read) {
  const auto [is_empty, value] = buffer_adaptor_multiskip_then_read();
  ASSERT_TRUE(is_empty);
  ASSERT_EQ(value, (std::array<std::uint8_t, 6>{1,2,3,4,5,6}[5]));
}

