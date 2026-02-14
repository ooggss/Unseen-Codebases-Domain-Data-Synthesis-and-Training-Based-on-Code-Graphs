
#include <gtest/gtest.h>
#include <cstring>
#include <string>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_4.hpp"

TEST(binary_stream_pmc, read_write_c_string) {
	const char* in{"The quick brown fox jumped over the lazy dog"};
	const auto result = exercise_read_write_c_string(in);

	ASSERT_EQ(result.size_after_write, std::strlen(in) + 1);
	ASSERT_TRUE(result.stream_empty);
	ASSERT_EQ(0, std::strcmp(in, result.out.c_str()));
	ASSERT_EQ(result.final_state, hexi::stream_state::ok) << "Unexpected stream state";
}
