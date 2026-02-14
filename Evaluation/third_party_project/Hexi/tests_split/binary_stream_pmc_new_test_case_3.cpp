
#include <gtest/gtest.h>
#include <string>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_3.hpp"

TEST(binary_stream_pmc, read_write_std_string) {
	const std::string in{"The quick brown fox jumped over the lazy dog"};
	const auto result = exercise_read_write_std_string(in);

	ASSERT_EQ(result.size_after_write, in.size() + 1); // +1 terminator
	ASSERT_TRUE(result.stream_empty);
	ASSERT_EQ(in, result.out);
	ASSERT_EQ(result.final_state, hexi::stream_state::ok) << "Unexpected stream state";
}
