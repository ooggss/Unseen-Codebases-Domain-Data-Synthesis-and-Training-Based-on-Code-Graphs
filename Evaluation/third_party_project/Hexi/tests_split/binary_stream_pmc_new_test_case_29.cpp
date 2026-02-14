
#include <gtest/gtest.h>
#include <string>
#include <vector>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_29.hpp"

TEST(binary_stream_pmc, iterable_containers) {
	const std::vector<int> primitives{1, 2, 3, 4, 5};
	const std::vector<std::string> strings{"hello, ", "world!"};

	const auto r = exercise_iterable_containers(primitives, strings);

	ASSERT_EQ(primitives.size() * sizeof(int), r.bytes_after_primitives);
	ASSERT_EQ(primitives.size() * sizeof(int), r.adaptor_size_after_primitives);
	ASSERT_EQ(primitives.size() * sizeof(int), r.backing_buffer_size_after_primitives);

	ASSERT_EQ(r.primitives_read_back, primitives);

	ASSERT_EQ(r.hello, "hello, ");
	ASSERT_EQ(r.world, "world!");

	Complex obj_in;
	ASSERT_EQ(obj_in.str, r.complex_str);

	const std::vector<int> expected_numbers{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	ASSERT_EQ(r.complex_numbers, expected_numbers);
}
