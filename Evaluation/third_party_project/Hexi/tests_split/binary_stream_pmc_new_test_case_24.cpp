
#include <gtest/gtest.h>
#include <string_view>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_24.hpp"

TEST(binary_stream_pmc, std_array) {
	const std::string_view input{"We're just normal strings. Innocent strings."};
	const auto r = exercise_std_array_behaviour(input);

	ASSERT_TRUE(r.initial_write_threw_buffer_overflow);
	ASSERT_TRUE(r.stream_empty_after_reset);

	ASSERT_TRUE(r.stream_empty_after_roundtrip);
	ASSERT_TRUE(r.stream_truthy_after_roundtrip);
	ASSERT_EQ(input, r.output);
}
