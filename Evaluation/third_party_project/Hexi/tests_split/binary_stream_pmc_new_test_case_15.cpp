
#include <gtest/gtest.h>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_15.hpp"

TEST(binary_stream_pmc, string_adaptor_prefixed_varint_long) {
	const auto r = exercise_prefixed_varint_string(80'000);
	ASSERT_EQ(r.input, r.output);
	ASSERT_TRUE(r.stream_empty);
	ASSERT_TRUE(r.stream_truthy);
}

TEST(binary_stream_pmc, string_adaptor_prefixed_varint_medium) {
	const auto r = exercise_prefixed_varint_string(5'000);
	ASSERT_EQ(r.input, r.output);
	ASSERT_TRUE(r.stream_empty);
	ASSERT_TRUE(r.stream_truthy);
}

TEST(binary_stream_pmc, string_adaptor_prefixed_varint_short) {
	const auto r = exercise_prefixed_varint_string(127);
	ASSERT_EQ(r.input, r.output);
	ASSERT_TRUE(r.stream_empty);
	ASSERT_TRUE(r.stream_truthy);
}
