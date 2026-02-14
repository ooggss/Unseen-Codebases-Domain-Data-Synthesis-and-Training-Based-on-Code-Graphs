
#include <gtest/gtest.h>
#include <array>
#include <cstdint>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_1.hpp"

TEST(binary_stream_pmc, buffer_limit) {
	const std::array<std::uint8_t, 14> ping{
		0x00, 0x0C, 0xDC, 0x01, 0x00, 0x00, 0x01,
		0x00, 0x00, 0x00, 0xF4, 0x01, 0x00, 0x00
	};

	const auto result = exercise_buffer_limit(ping);

	ASSERT_TRUE(result.first_read_succeeded) << "Failed to read packet back from stream";
	ASSERT_TRUE(result.second_read_threw_buffer_underrun) << "Message boundary was not respected";
	ASSERT_EQ(result.final_state, hexi::stream_state::buff_limit_err) << "Unexpected stream state";
}
