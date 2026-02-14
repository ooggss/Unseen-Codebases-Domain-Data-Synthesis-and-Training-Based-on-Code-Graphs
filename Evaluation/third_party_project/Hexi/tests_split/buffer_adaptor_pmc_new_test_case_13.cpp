
#include <gtest/gtest.h>
#include <tuple>
#include <cstdint>

#include "buffer_adaptor_pmc_function_implementation_13.hpp"

TEST(buffer_adaptor_pmc_split, read_ptr) {
	const auto [obs0, exp0, obs1, exp1, obs2, exp2] = pmc_split::buffer_adaptor_read_ptr_sequence();
	ASSERT_EQ(obs0, exp0);
	ASSERT_EQ(obs1, exp1);
	ASSERT_EQ(obs2, exp2);
}
