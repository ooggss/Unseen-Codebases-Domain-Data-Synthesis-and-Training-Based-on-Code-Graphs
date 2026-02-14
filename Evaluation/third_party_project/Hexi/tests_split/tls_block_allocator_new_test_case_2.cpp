
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>
#include <array>

// Include function implementation (normally via a header)
#include "tls_block_allocator_function_implementation_2.hpp"

TEST(tls_block_allocator, over_capacity) {
  const auto observed = tls_block_allocator_over_capacity_observe();

  ASSERT_EQ(observed[0], 1); // storage_active_count after 2 allocs
  ASSERT_EQ(observed[1], 1); // new_active_count after 2 allocs
  ASSERT_EQ(observed[2], 2); // total_allocs after 2 allocs
  ASSERT_EQ(observed[3], 0); // total_deallocs after 2 allocs

  ASSERT_EQ(observed[4], 0); // storage_active_count after dealloc mem[0]
  ASSERT_EQ(observed[5], 1); // new_active_count after dealloc mem[0]
  ASSERT_EQ(observed[6], 2); // total_allocs after dealloc mem[0]
  ASSERT_EQ(observed[7], 1); // total_deallocs after dealloc mem[0]

  ASSERT_EQ(observed[8], 0);  // storage_active_count after dealloc mem[1]
  ASSERT_EQ(observed[9], 0);  // new_active_count after dealloc mem[1]
  ASSERT_EQ(observed[10], 2); // total_allocs after dealloc mem[1]
  ASSERT_EQ(observed[11], 2); // total_deallocs after dealloc mem[1]
}
