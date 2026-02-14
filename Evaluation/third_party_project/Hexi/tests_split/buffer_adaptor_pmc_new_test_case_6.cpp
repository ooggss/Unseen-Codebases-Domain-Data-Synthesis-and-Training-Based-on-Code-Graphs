
#include <gtest/gtest.h>
#include <tuple>
#include <cstdint>
#include <cstddef>

#include "buffer_adaptor_pmc_function_implementation_6.hpp"

TEST(buffer_adaptor_pmc_split, single_skip_read) {
	const auto [remaining_size, value, expected] = pmc_split::buffer_adaptor_single_skip_read();
	ASSERT_EQ(remaining_size, 1u);
	ASSERT_EQ(value, expected);
}
