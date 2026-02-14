
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>

// Include function definition (in real projects, include via header)
#include "intrusive_storage_function_implementation_2.hpp"

TEST(intrusive_storage, skip) {
	// ============ Construct Function Inputs ============
	const char text[] = "The quick brown fox jumps over the lazy dog";
	const std::size_t skip_len = 4;

	// ============ Call Function ============
	const auto result = intrusive_storage_skip_and_read(text, sizeof(text), skip_len);

	// ============ Assert Return Value ============
	ASSERT_EQ(4u, result.skipped) << "Incorrect skip length";
	ASSERT_STREQ("quick brown fox jumps over the lazy dog", result.remainder.c_str())
		<< "Skip/read produced incorrect result";
}
