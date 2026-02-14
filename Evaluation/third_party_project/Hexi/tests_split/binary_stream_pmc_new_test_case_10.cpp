
#include <gtest/gtest.h>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_10.hpp"

TEST(binary_stream_pmc, fill) {
	const auto result = exercise_fill();

	ASSERT_EQ(result.size_after_fill_30, 30);
	ASSERT_EQ(result.total_write_after_fill_30, 30);
	ASSERT_EQ(result.size_after_fill_2_more, 32);
	ASSERT_EQ(result.total_write_after_fill_2_more, 32);
	ASSERT_TRUE(result.all_values_equal_128);
}
