
#include <gtest/gtest.h>
#include <tuple>
#include <cstddef>

#include "buffer_adaptor_pmc_function_implementation_9.hpp"

TEST(buffer_adaptor_pmc_split, write_append) {
	const auto [buffer_size, adaptor_size, equals] = pmc_split::buffer_adaptor_write_append_result();
	ASSERT_EQ(buffer_size, 6u);
	ASSERT_EQ(adaptor_size, buffer_size);
	ASSERT_TRUE(equals);
}
