
#include <gtest/gtest.h>
#include <string>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_28.hpp"

TEST(binary_stream_pmc, experimental_serialise) {
	const Foo input{
		.x = 100,
		.y = 200,
		.z = 300,
		.str = {"It's a fake!"}
	};

	const auto r = exercise_experimental_serialise(input);

	ASSERT_EQ(r.total_write, 29);

	Foo empty{};
	ASSERT_NE(input, empty);

	ASSERT_EQ(r.total_read, 29);
	ASSERT_EQ(r.remaining_size, 0);
	ASSERT_TRUE(r.stream_truthy);
	ASSERT_EQ(input, r.output);
}
