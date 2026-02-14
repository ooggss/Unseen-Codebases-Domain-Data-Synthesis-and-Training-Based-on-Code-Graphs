

#include <gtest/gtest.h>
#include <utility>

#include "buffer_adaptor_function_implementation_2.hpp"

TEST(buffer_adaptor, size_populated_initial) {
  const auto [adaptor_size, buffer_size] = buffer_adaptor_size_populated_initial();
  ASSERT_EQ(adaptor_size, buffer_size);
}

