
#include <hexi/pmc/binary_stream.h>
#include <hexi/dynamic_buffer.h>
#include <cstring>
#include <string>

struct ReadWriteCStringResult {
	std::size_t size_after_write;
	std::string out;
	bool stream_empty;
	hexi::stream_state final_state;
};

/**
 * @brief Serializes a C-string (const char*) and deserializes it as a null-terminated std::string.
 *
 * Writes the input C-string including its terminator using operator<<, then reads back using
 * hexi::null_terminated into a std::string.
 *
 * @param in Null-terminated C-string to write to the stream.
 * @return ReadWriteCStringResult Stream size after writing, deserialized std::string,
 *         stream emptiness after reading, and final stream state.
 */
ReadWriteCStringResult exercise_read_write_c_string(const char* in) {
	hexi::dynamic_buffer<32> buffer;
	hexi::pmc::binary_stream stream(buffer);

	stream << in;

	ReadWriteCStringResult res{};
	res.size_after_write = stream.size();

	std::string out;
	stream >> hexi::null_terminated(out);

	res.out = std::move(out);
	res.stream_empty = stream.empty();
	res.final_state = stream.state();
	return res;
}
