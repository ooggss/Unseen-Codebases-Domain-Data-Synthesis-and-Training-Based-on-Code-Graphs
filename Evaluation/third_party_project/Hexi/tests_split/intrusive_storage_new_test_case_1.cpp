
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>
#include <cstring>

// Include function definition (in real projects, include via header)
#include "intrusive_storage_function_implementation_1.hpp"

TEST(intrusive_storage, read_write_consistency) {
	// ============ Construct Function Inputs ============
	const char text[] = "The quick brown fox jumps over the lazy dog";

	// ============ Call Function ============
	const auto result = intrusive_storage_roundtrip_text(text, sizeof(text));

	// ============ Assert Return Value ============
	ASSERT_EQ(sizeof(text), result.written) << "Incorrect write size";
	ASSERT_EQ(sizeof(text), result.read) << "Incorrect read size";

	ASSERT_STREQ(text, result.text_out.c_str()) << "Read produced incorrect result";
	ASSERT_EQ(0u, result.final_size) << "Buffer should be empty";
}
