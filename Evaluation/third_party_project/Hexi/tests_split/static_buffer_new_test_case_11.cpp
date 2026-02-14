
#include <gtest/gtest.h>

#include <array>
#include <utility>

#include "static_buffer_function_implementation_11.hpp"

TEST(static_buffer, read_ptr) {
  const auto obs = static_buffer_read_ptr_impl();
  ASSERT_EQ(obs[0].first, obs[0].second);
  ASSERT_EQ(obs[1].first, obs[1].second);
  ASSERT_EQ(obs[2].first, obs[2].second);
}
