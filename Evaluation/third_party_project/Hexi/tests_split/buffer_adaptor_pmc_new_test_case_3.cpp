
#include <gtest/gtest.h>
#include <array>
#include <cstddef>

#include "buffer_adaptor_pmc_function_implementation_3.hpp"

TEST(buffer_adaptor_pmc_split, resize_match) {
	const auto sizes = pmc_split::buffer_adaptor_resize_match_sizes();
	ASSERT_EQ(sizes[0], sizes[1]);
	ASSERT_EQ(sizes[2], sizes[3]);
}
