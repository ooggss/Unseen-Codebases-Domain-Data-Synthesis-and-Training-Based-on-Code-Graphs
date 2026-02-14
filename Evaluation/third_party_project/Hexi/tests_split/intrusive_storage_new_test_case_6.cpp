
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>
#include <string_view>

// Include function definition (in real projects, include via header)
#include "intrusive_storage_function_implementation_6.hpp"

TEST(intrusive_storage, advance_write) {
	// ============ Construct Function Inputs ============
	constexpr std::string_view str{"A short string"};
	const std::size_t advance = 10;

	// ============ Call Function ============
	const auto result = intrusive_storage_advance_write_roundtrip(str, advance);

	// ============ Assert Return Value ============
	ASSERT_EQ(result.size_after_advance, advance);
	ASSERT_EQ(result.size_after_write, advance + str.size() + 1);
	ASSERT_STREQ(str.data(), result.out.c_str());
}
