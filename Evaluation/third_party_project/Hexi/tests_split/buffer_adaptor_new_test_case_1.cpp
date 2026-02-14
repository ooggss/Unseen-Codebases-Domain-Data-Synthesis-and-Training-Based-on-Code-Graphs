

#include <gtest/gtest.h>
#include <utility>

#include "buffer_adaptor_function_implementation_1.hpp"

TEST(buffer_adaptor, empty) {
  const auto [empty_initial, empty_after] =
      buffer_adaptor_empty_before_after_write_advance();

  ASSERT_TRUE(empty_initial);
  ASSERT_FALSE(empty_after);
}

