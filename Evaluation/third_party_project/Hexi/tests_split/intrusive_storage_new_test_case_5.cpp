
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>
#include <string_view>

// Include function definition (in real projects, include via header)
#include "intrusive_storage_function_implementation_5.hpp"

TEST(intrusive_storage, subscript) {
	// ============ Construct Function Inputs ============
	std::string_view str{"ABC"};

	// ============ Call Function ============
	const auto result = intrusive_storage_subscript_demo(str);

	// ============ Assert Return Value ============
	ASSERT_EQ(str[0], result.before0);
	ASSERT_EQ(str[1], result.before1);
	ASSERT_EQ(str[2], result.before2);

	ASSERT_EQ('C', result.after0);
	ASSERT_EQ('D', result.after1);
	ASSERT_EQ('E', result.after2);
}
