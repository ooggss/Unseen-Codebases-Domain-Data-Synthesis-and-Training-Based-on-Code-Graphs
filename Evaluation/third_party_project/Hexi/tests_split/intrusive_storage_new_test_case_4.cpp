
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>
#include <array>

// Include function definition (in real projects, include via header)
#include "intrusive_storage_function_implementation_4.hpp"

TEST(intrusive_storage, read_wrie_ints) {
	// ============ Construct Function Inputs ============
	std::array<int, 4> in{42, 1657, 1558, -1563};

	// ============ Call Function ============
	const auto result = intrusive_storage_write_read_ints(in);

	// ============ Assert Return Value ============
	ASSERT_EQ(sizeof(in), result.size_after_write);
	ASSERT_EQ(in, result.out);
	ASSERT_TRUE(result.empty_after_read);
}
