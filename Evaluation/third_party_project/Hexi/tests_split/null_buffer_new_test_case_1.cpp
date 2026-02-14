
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>

// Include function definition (in actual projects, should be included via a header)
#include "null_buffer_function_implementation_1.hpp"

namespace test_null_buffer_write_seek {

TEST(null_buffer, write_seek) {
	// Call function under test
	const bool did_throw = null_buffer_write_seek_throws();

	// Assertion
	ASSERT_TRUE(did_throw);
}

} // namespace test_null_buffer_write_seek
