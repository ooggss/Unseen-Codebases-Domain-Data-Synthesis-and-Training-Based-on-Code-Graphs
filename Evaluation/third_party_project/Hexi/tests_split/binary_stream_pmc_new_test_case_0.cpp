
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <gtest/gtest.h>
#include <array>
#include <cstdint>

// In real projects, include via a header.
#include "binary_stream_pmc_function_implementation_0.hpp"

TEST(binary_stream_pmc, message_read_limit) {
	const std::array<std::uint8_t, 14> ping{
		0x00, 0x0C, 0xDC, 0x01, 0x00, 0x00, 0x01,
		0x00, 0x00, 0x00, 0xF4, 0x01, 0x00, 0x00
	};

	const auto result = exercise_message_read_limit(ping);

	ASSERT_EQ(result.initial_read_limit, ping.size());
	ASSERT_TRUE(result.first_read_succeeded) << "Failed to read packet back from stream";
	ASSERT_TRUE(result.second_read_threw_read_limit) << "Message boundary was not respected";
	ASSERT_EQ(result.final_state, hexi::stream_state::read_limit_err) << "Unexpected stream state";
}
