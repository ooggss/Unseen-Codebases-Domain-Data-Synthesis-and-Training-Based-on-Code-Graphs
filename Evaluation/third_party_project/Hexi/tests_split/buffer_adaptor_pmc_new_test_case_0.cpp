
#include <gtest/gtest.h>
#include <cstddef>

// Include function definition (in actual projects, should be included via header file)
#include "buffer_adaptor_pmc_function_implementation_0.hpp"

TEST(buffer_adaptor_pmc_split, size_empty_initial) {
	const auto size = pmc_split::buffer_adaptor_size_empty_initial();
	ASSERT_EQ(size, 0u);
}
