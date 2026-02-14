
//  _               _ 
// | |__   _____  _(_)
// | '_ \ / _ \ \/ / | MIT & Apache 2.0 dual licensed
// | | | |  __/>  <| | Version 1.0
// |_| |_|\___/_/\_\_| https://github.com/EmberEmu/hexi

#include <hexi/pmc/binary_stream.h>
#include <hexi/dynamic_buffer.h>
#include <array>
#include <cstdint>

struct MessageReadLimitResult {
	std::size_t initial_read_limit;
	hexi::stream_state final_state;
	bool first_read_succeeded;
	bool second_read_threw_read_limit;
};

/**
 * @brief Exercises hexi::pmc::binary_stream message read-limit enforcement.
 *
 * Writes the same "ping" packet twice into a dynamic buffer, then creates a binary_stream
 * with a per-message read limit equal to the packet size. It performs one successful read
 * of a full packet and then attempts to read past the message boundary, which should throw
 * hexi::stream_read_limit and place the stream into read_limit_err state.
 *
 * @param ping_packet The 14-byte ping packet payload to write twice and read back.
 * @return MessageReadLimitResult Captures the stream's read_limit(), whether the first read
 *         succeeded, whether the second read threw stream_read_limit, and the final stream state.
 */
MessageReadLimitResult exercise_message_read_limit(const std::array<std::uint8_t, 14>& ping_packet) {
	std::array<std::uint8_t, 14> ping = ping_packet;

	hexi::dynamic_buffer<32> buffer;
	buffer.write(ping.data(), ping.size());
	buffer.write(ping.data(), ping.size());

	hexi::pmc::binary_stream stream(buffer, ping.size());

	MessageReadLimitResult res{};
	res.initial_read_limit = stream.read_limit();

	try {
		stream.get(ping.data(), ping.size());
		res.first_read_succeeded = true;
	} catch(...) {
		res.first_read_succeeded = false;
	}

	try {
		stream.get(ping.data(), ping.size());
		res.second_read_threw_read_limit = false;
	} catch(const hexi::stream_read_limit&) {
		res.second_read_threw_read_limit = true;
	}

	res.final_state = stream.state();
	return res;
}
