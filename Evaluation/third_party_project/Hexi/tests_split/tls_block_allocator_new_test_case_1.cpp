
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>
#include <cstdint>

// Include function implementation (normally via a header)
#include "tls_block_allocator_function_implementation_1.hpp"

TEST(tls_block_allocator, random_allocs) {
  const auto max_allocs = 100u;

  const auto observed = tls_block_allocator_random_allocs_observe(max_allocs);

  const auto allocs = static_cast<std::uint64_t>(observed[0]);
  const auto tls_total_alloc_before = observed[1];
  const auto tls_total_dealloc_before = observed[2];

  ASSERT_EQ(observed[3], allocs);                    // tlsalloc.total_allocs
  ASSERT_EQ(observed[4], allocs);                    // tlsalloc.active_allocs
  ASSERT_EQ(observed[5], 0);                         // tlsalloc.total_deallocs
  ASSERT_EQ(observed[6], tls_total_alloc_before + allocs); // underlying total_allocs
  ASSERT_EQ(observed[7], tls_total_dealloc_before);        // underlying total_deallocs

  ASSERT_EQ(observed[3], allocs);                    // tlsalloc.total_allocs (unchanged)
  ASSERT_EQ(observed[8], 0);                         // tlsalloc.active_allocs after dealloc
  ASSERT_EQ(observed[9], allocs);                    // tlsalloc.total_deallocs after dealloc
  ASSERT_EQ(observed[6], tls_total_alloc_before + allocs); // underlying total_allocs (unchanged)
  ASSERT_EQ(observed[10], tls_total_dealloc_before + allocs); // underlying total_deallocs after dealloc
}
