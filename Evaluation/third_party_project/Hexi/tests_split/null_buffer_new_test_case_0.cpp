
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>
#include <string_view>
#include <array>
#include <utility>

// Include function definition (in actual projects, should be included via a header)
#include "null_buffer_function_implementation_0.hpp"

namespace test_null_buffer_write_size {

TEST(null_buffer, write_size) {
	// Inputs
	std::string_view str { "A library serves no purpose unless someone is using it." };

	// Call function under test
	const auto [totals, buffer_empty] = write_and_measure_total_bytes(str);

	// Assertions (derived from returned values)
	ASSERT_EQ(totals[0], 1);
	ASSERT_EQ(totals[1], 3);
	ASSERT_EQ(totals[2], 7);
	ASSERT_EQ(totals[3], 15);
	ASSERT_EQ(totals[4], 71);
	ASSERT_TRUE(buffer_empty);
}

} // namespace test_null_buffer_write_size
