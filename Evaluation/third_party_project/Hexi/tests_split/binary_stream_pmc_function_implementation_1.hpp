
#include <hexi/pmc/binary_stream.h>
#include <hexi/dynamic_buffer.h>
#include <array>
#include <cstdint>

struct BufferLimitResult {
	bool first_read_succeeded;
	bool second_read_threw_buffer_underrun;
	hexi::stream_state final_state;
};

/**
 * @brief Exercises buffer underrun handling in hexi::pmc::binary_stream.
 *
 * Writes a single ping packet into a dynamic buffer, reads it back completely,
 * then attempts to read another packet past the end of the buffer. The second read
 * is expected to throw hexi::buffer_underrun and set the stream state to buff_limit_err.
 *
 * @param ping_packet The ping packet bytes to write and attempt to read twice.
 * @return BufferLimitResult Indicates whether the first read succeeded, whether the second
 *         read threw buffer_underrun, and the final stream state.
 */
BufferLimitResult exercise_buffer_limit(const std::array<std::uint8_t, 14>& ping_packet) {
	std::array<std::uint8_t, 14> ping = ping_packet;

	hexi::dynamic_buffer<32> buffer;
	buffer.write(ping.data(), ping.size());

	hexi::pmc::binary_stream stream(buffer);

	BufferLimitResult res{};

	try {
		stream.get(ping.data(), ping.size());
		res.first_read_succeeded = true;
	} catch(...) {
		res.first_read_succeeded = false;
	}

	try {
		stream.get(ping.data(), ping.size());
		res.second_read_threw_buffer_underrun = false;
	} catch(const hexi::buffer_underrun&) {
		res.second_read_threw_buffer_underrun = true;
	}

	res.final_state = stream.state();
	return res;
}
