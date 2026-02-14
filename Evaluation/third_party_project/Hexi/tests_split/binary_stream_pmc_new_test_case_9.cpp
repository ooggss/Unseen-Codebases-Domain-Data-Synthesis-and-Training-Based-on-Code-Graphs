
#include <gtest/gtest.h>
#include <cstdint>
#include <vector>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_9.hpp"

TEST(binary_stream_pmc, get_put) {
	const std::vector<std::uint8_t> in{1, 2, 3, 4, 5};
	const auto result = exercise_get_put(in);

	ASSERT_EQ(result.total_read, in.size());
	ASSERT_EQ(result.total_write, in.size());
	ASSERT_EQ(in, result.out);
}
