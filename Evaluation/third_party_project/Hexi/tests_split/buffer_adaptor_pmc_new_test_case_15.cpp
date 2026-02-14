
#include <gtest/gtest.h>
#include <tuple>
#include <cstddef>

#include "buffer_adaptor_pmc_function_implementation_15.hpp"

TEST(buffer_adaptor_pmc_split, find_first_of) {
	const auto [pos0, npos, pos_g, pos_T, pos_t] = pmc_split::buffer_adaptor_find_first_of_positions();
	ASSERT_EQ(pos0, npos);
	ASSERT_EQ(pos_g, 43u);
	ASSERT_EQ(pos_T, 0u);
	ASSERT_EQ(pos_t, 32u);
}
