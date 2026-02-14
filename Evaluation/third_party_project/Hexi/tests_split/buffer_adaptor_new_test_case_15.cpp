

#include <gtest/gtest.h>

#include "buffer_adaptor_function_implementation_15.hpp"

TEST(buffer_adaptor, find_first_of) {
  const auto out = buffer_adaptor_find_first_of_outcome();
  ASSERT_EQ(out.pos_null, out.npos); // direct string write is not terminated
  ASSERT_EQ(out.pos_g, 43);
  ASSERT_EQ(out.pos_T, 0);
  ASSERT_EQ(out.pos_t, 32);
}

