
#include <gtest/gtest.h>
#include <string_view>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_23.hpp"

TEST(binary_stream_pmc, string_view_adaptor_null_terminated) {
	const std::string_view input{"We're just normal strings. Innocent strings."};
	const auto r = exercise_string_view_adaptor_null_terminated(input);

	ASSERT_EQ(r.size_after_write, input.size() + 1); // +1 null terminator
	ASSERT_EQ(input, r.output);
	ASSERT_TRUE(r.stream_empty);
}
