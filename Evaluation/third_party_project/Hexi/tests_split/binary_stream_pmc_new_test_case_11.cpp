
#include <gtest/gtest.h>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_11.hpp"

TEST(binary_stream_pmc, array) {
	const int arr[] = {1, 2, 3};
	const auto result = exercise_array_write_read_first3(arr, 3);

	ASSERT_EQ(result.first, 1);
	ASSERT_EQ(result.second, 2);
	ASSERT_EQ(result.third, 3);
}
