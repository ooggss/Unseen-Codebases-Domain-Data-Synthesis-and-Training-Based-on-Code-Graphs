
#include <gtest/gtest.h>
#include <utility>
#include <cstddef>

#include "buffer_adaptor_pmc_function_implementation_2.hpp"

TEST(buffer_adaptor_pmc_split, size_populated_initial) {
	const auto [adaptor_size, buffer_size] = pmc_split::buffer_adaptor_size_populated_initial();
	ASSERT_EQ(adaptor_size, buffer_size);
}
