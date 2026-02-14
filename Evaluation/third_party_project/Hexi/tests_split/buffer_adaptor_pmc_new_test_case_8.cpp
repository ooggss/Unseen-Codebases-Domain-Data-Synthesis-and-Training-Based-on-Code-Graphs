
#include <gtest/gtest.h>
#include <tuple>
#include <cstddef>

#include "buffer_adaptor_pmc_function_implementation_8.hpp"

TEST(buffer_adaptor_pmc_split, write) {
	const auto [size_after_array, buffer_size_after_array, equals, size_after_single] =
	    pmc_split::buffer_adaptor_write_and_append_one();

	ASSERT_EQ(size_after_array, 6u);
	ASSERT_EQ(buffer_size_after_array, 6u);
	ASSERT_TRUE(equals);
	ASSERT_EQ(size_after_single, size_after_array + 1);
}
