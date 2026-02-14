
#include <gtest/gtest.h>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <random>
#include <ranges>
#include <vector>
#include <cstdlib>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_5.hpp"

TEST(binary_stream_pmc, read_write_vector) {
	const auto time = std::chrono::system_clock::now().time_since_epoch();
	const unsigned int seed = static_cast<unsigned int>(time.count());
	std::srand(seed);

	std::vector<int> in(std::rand() % 200);
	std::ranges::iota(in, std::rand() % 100);
	std::ranges::shuffle(in, std::default_random_engine(seed));

	const auto result = exercise_read_write_vector(in);

	ASSERT_EQ(result.first_pass_values, in);
	ASSERT_EQ(result.second_pass_out, in);
	ASSERT_EQ(result.final_state, hexi::stream_state::ok) << "Unexpected stream state";
}
