
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>
#include <array>

// Include function implementation (normally via a header)
#include "tls_block_allocator_function_implementation_0.hpp"

TEST(tls_block_allocator, single_alloc) {
  const auto observed = tls_block_allocator_single_alloc_observe();

  ASSERT_EQ(observed[0], 1); // storage_active_count after allocate
  ASSERT_EQ(observed[1], 0); // new_active_count after allocate
  ASSERT_EQ(observed[2], 1); // total_allocs after allocate
  ASSERT_EQ(observed[3], 0); // total_deallocs after allocate

  ASSERT_EQ(observed[4], 0); // storage_active_count after deallocate
  ASSERT_EQ(observed[5], 0); // new_active_count after deallocate
  ASSERT_EQ(observed[6], 1); // total_allocs after deallocate
  ASSERT_EQ(observed[7], 1); // total_deallocs after deallocate
}
