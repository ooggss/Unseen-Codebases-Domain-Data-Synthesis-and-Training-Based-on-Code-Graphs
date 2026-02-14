

#include <gtest/gtest.h>
#include <string_view>

using namespace std::literals;

#include "buffer_adaptor_function_implementation_16.hpp"

TEST(buffer_adaptor, string_buffer) {
  const auto buffer = buffer_adaptor_write_into_string_buffer();
  const auto str = "The quick brown fox jumped over the lazy dog"sv;
  ASSERT_EQ(buffer, str);
}

