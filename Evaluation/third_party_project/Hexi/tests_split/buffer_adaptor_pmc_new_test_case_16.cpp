
#include <gtest/gtest.h>
#include <string_view>

#include "buffer_adaptor_pmc_function_implementation_16.hpp"

using namespace std::literals;

TEST(buffer_adaptor_pmc_split, string_buffer) {
	const auto str = "The quick brown fox jumped over the lazy dog"sv;
	const auto buffer = pmc_split::buffer_adaptor_write_into_string(str);
	ASSERT_EQ(buffer, str);
}
