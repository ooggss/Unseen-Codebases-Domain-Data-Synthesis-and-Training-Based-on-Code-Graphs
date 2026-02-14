
#include <gtest/gtest.h>
#include <string>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_19.hpp"

TEST(binary_stream_pmc, string_adaptor_null_terminated) {
	const std::string input{"We're just normal strings. Innocent strings."};
	const auto r = exercise_string_adaptor_null_terminated(input);

	ASSERT_EQ(input, r.output);
	ASSERT_TRUE(r.stream_empty);
}
