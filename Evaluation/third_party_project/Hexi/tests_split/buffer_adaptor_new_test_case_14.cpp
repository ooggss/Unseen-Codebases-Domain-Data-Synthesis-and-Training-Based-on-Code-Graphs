

#include <gtest/gtest.h>

#include "buffer_adaptor_function_implementation_14.hpp"

TEST(buffer_adaptor, subscript) {
  const auto out = buffer_adaptor_subscript_outcome();
  ASSERT_EQ(out.initial0, 1);
  ASSERT_EQ(out.initial1, 2);
  ASSERT_EQ(out.initial2, 3);
  ASSERT_EQ(out.after_buffer_mutation0, 4);
  ASSERT_EQ(out.after_adaptor_mutation0, 5);
  ASSERT_EQ(out.after_adaptor_mutation0, out.final_buffer0);
}

