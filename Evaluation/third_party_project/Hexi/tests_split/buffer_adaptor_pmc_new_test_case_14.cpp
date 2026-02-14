
#include <gtest/gtest.h>
#include <tuple>
#include <cstddef>

#include "buffer_adaptor_pmc_function_implementation_14.hpp"

TEST(buffer_adaptor_pmc_split, subscript) {
	const auto [b0, b1, b2, b0_after] = pmc_split::buffer_adaptor_subscript_observations();
	ASSERT_EQ(b0, std::byte(1));
	ASSERT_EQ(b1, std::byte(2));
	ASSERT_EQ(b2, std::byte(3));
	ASSERT_EQ(b0_after, std::byte(4));
}
