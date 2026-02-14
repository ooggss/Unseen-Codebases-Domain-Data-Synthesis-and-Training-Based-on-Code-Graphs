
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>
#include <cstddef>

// Include function definition (in real projects, include via header)
#include "intrusive_storage_function_implementation_0.hpp"

TEST(intrusive_storage, size) {
	// ============ Construct Function Inputs ============
	const int iterations = 5;
	const int foo = 24221;

	// ============ Call Function ============
	const auto result = intrusive_storage_size_behavior(iterations, foo);

	// ============ Assert Return Value ============
	ASSERT_EQ(sizeof(int) * iterations, result.written_after_loop) << "Number of bytes written is incorrect";
	ASSERT_EQ(sizeof(int) * iterations, result.size_after_loop) << "Buffer size is incorrect";

	// attempt to exceed capacity - write should return 0
	ASSERT_EQ(0u, result.written_overflow_attempt) << "Number of bytes written is incorrect";
	ASSERT_EQ(sizeof(int) * iterations, result.size_after_overflow_attempt) << "Buffer size is incorrect";
}
