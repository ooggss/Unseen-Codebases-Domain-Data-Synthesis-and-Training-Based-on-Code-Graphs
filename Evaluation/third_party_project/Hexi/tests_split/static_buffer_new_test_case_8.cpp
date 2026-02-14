
#include <gtest/gtest.h>

#include "static_buffer_function_implementation_8.hpp"

TEST(static_buffer, can_write_seek) {
  ASSERT_TRUE(static_buffer_can_write_seek_impl());
}
