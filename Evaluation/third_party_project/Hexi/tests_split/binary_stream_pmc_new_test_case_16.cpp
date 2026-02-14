
#include <gtest/gtest.h>
#include <string>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_16.hpp"

TEST(binary_stream_pmc, string_adaptor_prefixed) {
	const std::string input{"The quick brown fox jumped over the lazy dog"};
	const auto r = exercise_string_adaptor_prefixed(input);

	ASSERT_EQ(input, r.output);
	ASSERT_TRUE(r.stream_empty);
}
