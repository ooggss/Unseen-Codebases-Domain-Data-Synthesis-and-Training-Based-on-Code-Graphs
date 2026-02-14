
#include <gtest/gtest.h>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_31.hpp"

TEST(binary_stream_pmc, std_array_size) {
	const auto r = exercise_std_array_size();
	ASSERT_TRUE(r.adaptor_empty);
	ASSERT_EQ(r.adaptor_size, 0);
	ASSERT_EQ(r.stream_size, 0);
}
