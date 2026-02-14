
#include <gtest/gtest.h>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_8.hpp"

TEST(binary_stream_pmc, can_write_seek) {
	const auto result = exercise_can_write_seek();
	ASSERT_EQ(result.buffer_can_write_seek, result.stream_can_write_seek);
}
