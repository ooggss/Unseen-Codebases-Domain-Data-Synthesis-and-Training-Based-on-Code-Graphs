
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>
#include <string_view>

// Include function definition (in real projects, include via header)
#include "intrusive_storage_function_implementation_3.hpp"

TEST(intrusive_storage, read_write_string_view) {
	// ============ Construct Function Inputs ============
	std::string_view str{"The quick brown fox jumped over the lazy dog"};

	// ============ Call Function ============
	const auto result = intrusive_storage_write_read_string_view(str);

	// ============ Assert Return Value ============
	ASSERT_EQ(str.size(), result.size_after_write);
	ASSERT_STREQ(str.data(), result.out.c_str());
	ASSERT_TRUE(result.empty_after_read);
}
