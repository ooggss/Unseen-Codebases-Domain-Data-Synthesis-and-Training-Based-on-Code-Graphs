
#include <hexi/pmc/binary_stream.h>
#include <hexi/dynamic_buffer.h>
#include <string>

struct ReadWriteStdStringResult {
	std::size_t size_after_write;
	std::string out;
	bool stream_empty;
	hexi::stream_state final_state;
};

/**
 * @brief Serializes and deserializes a std::string as a null-terminated string.
 *
 * Writes the input string using hexi::null_terminated wrapper (which appends a '\0'),
 * captures stream size after writing, then reads back into a std::string using the same wrapper.
 *
 * @param in The input std::string to serialize (null-terminated on the wire).
 * @return ReadWriteStdStringResult Stream size after write, the deserialized string,
 *         whether the stream is empty after read, and final stream state.
 */
ReadWriteStdStringResult exercise_read_write_std_string(const std::string& in) {
	hexi::dynamic_buffer<32> buffer;
	hexi::pmc::binary_stream stream(buffer);

	stream << hexi::null_terminated(in);

	ReadWriteStdStringResult res{};
	res.size_after_write = stream.size();

	std::string out;
	stream >> hexi::null_terminated(out);

	res.out = std::move(out);
	res.stream_empty = stream.empty();
	res.final_state = stream.state();
	return res;
}
