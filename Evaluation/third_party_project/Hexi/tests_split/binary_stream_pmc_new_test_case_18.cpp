
#include <gtest/gtest.h>
#include <format>
#include <string>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_18.hpp"

TEST(binary_stream_pmc, string_adaptor_raw) {
	const auto input = std::format("String with {} embedded null", '\0');
	const auto r = exercise_string_adaptor_raw(input);

	ASSERT_EQ(r.input_size, r.buffer_size_after_write);
	ASSERT_EQ(r.output_null_terminated, "String with ");
	ASSERT_FALSE(r.stream_empty_after_read);
}
