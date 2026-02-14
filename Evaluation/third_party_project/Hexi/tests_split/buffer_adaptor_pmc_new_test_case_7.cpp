
#include <gtest/gtest.h>
#include <tuple>
#include <cstdint>

#include "buffer_adaptor_pmc_function_implementation_7.hpp"

TEST(buffer_adaptor_pmc_split, multiskip_read) {
	const auto [is_empty, value, expected] = pmc_split::buffer_adaptor_multiskip_read();
	ASSERT_TRUE(is_empty);
	ASSERT_EQ(value, expected);
}
