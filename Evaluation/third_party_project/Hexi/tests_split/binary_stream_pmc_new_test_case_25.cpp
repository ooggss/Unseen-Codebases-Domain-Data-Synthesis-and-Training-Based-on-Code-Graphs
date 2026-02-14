
#include <gtest/gtest.h>
#include <string_view>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_25.hpp"

TEST(binary_stream_pmc, total_write_consistency) {
	const std::string_view str{"hello, world!"};
	const auto r = exercise_total_write_consistency(str);

	ASSERT_EQ(r.after_u8, 1);
	ASSERT_EQ(r.after_u16, 3);
	ASSERT_EQ(r.after_u32, 7);
	ASSERT_EQ(r.after_u64, 15);

	ASSERT_EQ(r.after_raw, 28);
	ASSERT_EQ(r.after_prefixed, 45);
	ASSERT_EQ(r.after_prefixed_varint, 59);
	ASSERT_EQ(r.after_null_terminated, 73);

	ASSERT_EQ(r.after_put_u8, 74);
	ASSERT_EQ(r.after_put_u16, 76);
	ASSERT_EQ(r.after_put_u32, 80);
	ASSERT_EQ(r.after_put_u64, 88);

	ASSERT_EQ(r.after_put_array, 104);
	ASSERT_EQ(r.after_put_ptr_count, 120);
	ASSERT_EQ(r.after_put_iterators, 136);
}
