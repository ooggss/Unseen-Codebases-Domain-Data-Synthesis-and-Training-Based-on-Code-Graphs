
#include <gtest/gtest.h>
#include <vector>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_30.hpp"

TEST(binary_stream_pmc, prefixed_containers) {
	const std::vector<int> primitives{1, 2, 3, 4, 5};

	std::vector<PrefixedContainers> objects;
	for (int i = 0u; i < 5; ++i) {
		objects.emplace_back(PrefixedContainers{{1 + i, 2 + i}, {3 + i, 4 + i}});
	}

	const auto r = exercise_prefixed_containers(primitives, objects);

	ASSERT_TRUE(std::ranges::equal(primitives, r.output_primitives));
	EXPECT_EQ(objects.size(), r.output_objs.size());
	ASSERT_EQ(objects, r.output_objs);
}
