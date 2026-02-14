
#include <gtest/gtest.h>
#include <string_view>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_13.hpp"

TEST(binary_stream_pmc, string_view_write) {
	const std::string_view view{"There's coffee in that nebula"};
	const auto result = exercise_string_view_write(view);
	ASSERT_EQ(view, result.res);
}
