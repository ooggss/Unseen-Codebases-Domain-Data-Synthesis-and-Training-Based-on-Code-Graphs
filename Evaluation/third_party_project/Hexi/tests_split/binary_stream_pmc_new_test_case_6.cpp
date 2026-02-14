
#include <gtest/gtest.h>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_6.hpp"

TEST(binary_stream_pmc, clear) {
	const auto result = exercise_clear_via_skip_all();

	ASSERT_TRUE(result.stream_non_empty_after_write);
	ASSERT_TRUE(result.buffer_non_empty_after_write);
	ASSERT_TRUE(result.stream_empty_after_skip);
	ASSERT_TRUE(result.buffer_empty_after_skip);
}
