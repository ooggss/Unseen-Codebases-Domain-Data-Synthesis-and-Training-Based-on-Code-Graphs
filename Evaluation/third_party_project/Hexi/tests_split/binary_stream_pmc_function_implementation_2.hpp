
#include <hexi/pmc/binary_stream.h>
#include <hexi/dynamic_buffer.h>
#include <cstdint>

struct ReadWriteIntsResult {
	std::size_t size_after_write;
	std::size_t buffer_size_after_write;
	std::uint16_t out_value;
	bool stream_empty;
	bool buffer_empty;
	hexi::stream_state final_state;
};

/**
 * @brief Writes a 16-bit integer to a binary_stream and reads it back.
 *
 * Creates a dynamic_buffer and binary_stream, serializes the input uint16_t using operator<<,
 * verifies size accounting by returning the stream/buffer sizes after writing, then deserializes
 * using operator>>. Also reports emptiness of stream/buffer and final stream state.
 *
 * @param in The uint16_t value to write then read back.
 * @return ReadWriteIntsResult Observations including sizes after write, the read-back value,
 *         whether stream/buffer are empty at end, and stream state.
 */
ReadWriteIntsResult exercise_read_write_ints(std::uint16_t in) {
	hexi::dynamic_buffer<32> buffer;
	hexi::pmc::binary_stream stream(buffer);

	stream << in;

	ReadWriteIntsResult res{};
	res.size_after_write = stream.size();
	res.buffer_size_after_write = buffer.size();

	std::uint16_t out{};
	stream >> out;

	res.out_value = out;
	res.stream_empty = stream.empty();
	res.buffer_empty = buffer.empty();
	res.final_state = stream.state();
	return res;
}
