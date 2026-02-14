
#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_12.hpp"

TEST(binary_stream_pmc, put_integral_literals) {
	const auto r = exercise_put_integral_literals();

	ASSERT_FLOAT_EQ(1.5f, r.resultf);
	ASSERT_DOUBLE_EQ(3.0, r.resultd);

	ASSERT_EQ(r.resultu8, std::numeric_limits<std::uint8_t>::max());
	ASSERT_EQ(r.resultu16, std::numeric_limits<std::uint16_t>::max());
	ASSERT_EQ(r.resultu32, std::numeric_limits<std::uint32_t>::max());
	ASSERT_EQ(r.resultu64, std::numeric_limits<std::uint64_t>::max());

	ASSERT_EQ(r.result8, std::numeric_limits<std::int8_t>::max());
	ASSERT_EQ(r.result16, std::numeric_limits<std::int16_t>::max());
	ASSERT_EQ(r.result32, std::numeric_limits<std::int32_t>::max());
	ASSERT_EQ(r.result64, std::numeric_limits<std::int64_t>::max());

	ASSERT_TRUE(r.stream_truthy);
}
