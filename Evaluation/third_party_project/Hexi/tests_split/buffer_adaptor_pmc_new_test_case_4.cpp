
#include <gtest/gtest.h>
#include <tuple>
#include <cstddef>
#include <cstdint>

#include "buffer_adaptor_pmc_function_implementation_4.hpp"

TEST(buffer_adaptor_pmc_split, read_one) {
	const auto [remaining_size, value, original_size] = pmc_split::buffer_adaptor_read_one_result();
	ASSERT_EQ(remaining_size, original_size - 1);
	ASSERT_EQ(value, 1);
}
