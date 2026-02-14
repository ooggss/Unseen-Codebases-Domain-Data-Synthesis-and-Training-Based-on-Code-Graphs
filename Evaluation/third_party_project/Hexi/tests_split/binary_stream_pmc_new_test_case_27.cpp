
#include <gtest/gtest.h>
#include <cstdint>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_27.hpp"

TEST(binary_stream, endianness_override_mismatch) {
	const std::uint64_t input = 100;
	const auto r = exercise_endianness_override_mismatch(input);

	ASSERT_NE(input, r.le_written_be_read);
	ASSERT_NE(input, r.be_written_le_read);
}
