
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>

// Include function implementation (normally via a header)
#include "tls_block_allocator_function_implementation_4.hpp"

TEST(tls_block_allocator, thread_mismatch) {
  ASSERT_DEATH(tls_block_allocator_thread_mismatch_death_triggers(), "");
}
