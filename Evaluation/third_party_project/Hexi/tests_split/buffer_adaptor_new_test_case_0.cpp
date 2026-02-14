

#include <gtest/gtest.h>
#include <cstddef>

// In a real project, include via a header.
#include "buffer_adaptor_function_implementation_0.hpp"

TEST(buffer_adaptor, size_empty_initial) {
  const auto size = buffer_adaptor_size_empty_initial();
  ASSERT_EQ(size, 0);
}

