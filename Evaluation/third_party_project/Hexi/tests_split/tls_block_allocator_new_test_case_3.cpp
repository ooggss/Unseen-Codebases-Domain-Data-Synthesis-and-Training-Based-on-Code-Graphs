
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>
#include <array>

// Include function implementation (normally via a header)
#include "tls_block_allocator_function_implementation_3.hpp"

TEST(tls_block_allocator, no_sharing) {
  const auto observed = tls_block_allocator_no_sharing_observe();

  const auto main_tls_total_alloc_before = observed[0];
  const auto main_tls_total_dealloc_before = observed[1];

  ASSERT_EQ(observed[2], 1); // main storage_active_count after alloc
  ASSERT_EQ(observed[3], main_tls_total_alloc_before + 1); // main total_allocs after alloc

  ASSERT_EQ(observed[4], 0); // thread allocator total_allocs initially
  ASSERT_EQ(observed[5], 0); // thread allocator storage_active_count initially
  ASSERT_EQ(observed[6], 1); // thread allocator total_allocs after alloc

  ASSERT_EQ(observed[7], main_tls_total_dealloc_before + 1); // main total_deallocs after dealloc
}
