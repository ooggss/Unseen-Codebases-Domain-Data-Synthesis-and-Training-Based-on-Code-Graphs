
#include <gtest/gtest.h>
#include <utility>

#include "buffer_adaptor_pmc_function_implementation_1.hpp"

TEST(buffer_adaptor_pmc_split, empty) {
	const auto [empty_before, empty_after] = pmc_split::buffer_adaptor_empty_before_after_one_write();
	ASSERT_TRUE(empty_before);
	ASSERT_FALSE(empty_after);
}
