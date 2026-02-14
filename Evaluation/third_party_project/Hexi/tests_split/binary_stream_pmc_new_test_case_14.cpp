
#include <gtest/gtest.h>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_14.hpp"

TEST(binary_stream_pmc, set_error_state) {
	const auto r = exercise_set_error_state();

	ASSERT_TRUE(r.initial_truthy);
	ASSERT_TRUE(r.initial_good);
	ASSERT_TRUE(r.initial_state == hexi::stream_state::ok);

	ASSERT_FALSE(r.final_truthy);
	ASSERT_FALSE(r.final_good);
	ASSERT_TRUE(r.final_state == hexi::stream_state::user_defined_err);
}
