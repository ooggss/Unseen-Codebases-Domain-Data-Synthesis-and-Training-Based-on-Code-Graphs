
#include <gtest/gtest.h>
#include <cstdint>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_7.hpp"

TEST(binary_stream_pmc, skip) {
	const std::uint64_t in{0xBADF00D};
	const auto result = exercise_skip(in);

	ASSERT_EQ(result.remaining_size, sizeof(in));
	ASSERT_EQ(result.remaining_size, result.remaining_buffer_size);
	ASSERT_TRUE(result.stream_empty_after_read);
	ASSERT_EQ(in, result.out_value);
}
