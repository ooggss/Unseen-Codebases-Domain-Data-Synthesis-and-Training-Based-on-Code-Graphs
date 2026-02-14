
#include <gtest/gtest.h>
#include <cstdint>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_2.hpp"

TEST(binary_stream_pmc, read_write_ints) {
	const std::uint16_t in{100};
	const auto result = exercise_read_write_ints(in);

	ASSERT_EQ(result.size_after_write, sizeof(in));
	ASSERT_EQ(result.size_after_write, result.buffer_size_after_write);
	ASSERT_EQ(in, result.out_value);
	ASSERT_TRUE(result.stream_empty);
	ASSERT_TRUE(result.buffer_empty);
	ASSERT_EQ(result.final_state, hexi::stream_state::ok) << "Unexpected stream state";
}
