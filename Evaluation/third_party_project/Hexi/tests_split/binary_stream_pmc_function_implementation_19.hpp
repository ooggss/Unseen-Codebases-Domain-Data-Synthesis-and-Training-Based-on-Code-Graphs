
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <string>
#include <vector>

struct StringAdaptorNullTerminatedResult {
	std::string output;
	bool stream_empty;
};

/**
 * @brief Round-trips a string using hexi::null_terminated with a vector<char> backing buffer.
 *
 * @param input The input string to write and read.
 * @return StringAdaptorNullTerminatedResult Output string and whether the stream is empty after read.
 */
StringAdaptorNullTerminatedResult exercise_string_adaptor_null_terminated(const std::string& input) {
	std::vector<char> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	hexi::pmc::binary_stream stream(adaptor);

	stream << hexi::null_terminated(input);

	std::string output;
	stream >> hexi::null_terminated(output);

	return {std::move(output), stream.empty()};
}
