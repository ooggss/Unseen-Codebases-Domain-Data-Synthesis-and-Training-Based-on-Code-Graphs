
#include <gtest/gtest.h>
#include <array>
#include <ranges>
#include <utility>
#include <cstdint>

#include "buffer_adaptor_pmc_function_implementation_5.hpp"

TEST(buffer_adaptor_pmc_split, read_all) {
	const auto [expected, values] = pmc_split::buffer_adaptor_read_all_values();
	ASSERT_TRUE(std::ranges::equal(expected, values));
}
