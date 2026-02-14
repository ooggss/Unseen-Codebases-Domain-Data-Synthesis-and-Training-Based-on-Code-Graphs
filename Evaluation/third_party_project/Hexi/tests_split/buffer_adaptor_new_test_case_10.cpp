

#include <gtest/gtest.h>

#include "buffer_adaptor_function_implementation_10.hpp"

TEST(buffer_adaptor, can_write_seek) {
  ASSERT_TRUE(buffer_adaptor_can_write_seek());
}

