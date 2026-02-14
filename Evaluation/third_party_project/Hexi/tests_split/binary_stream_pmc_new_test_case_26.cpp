
#include <gtest/gtest.h>
#include <cstdint>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_26.hpp"

TEST(binary_stream, endianness_override_match) {
	const std::uint64_t input = 100;
	const auto r = exercise_endianness_override_match(input);

	ASSERT_EQ(input, r.le_out);
	ASSERT_EQ(input, r.be_out);
}
