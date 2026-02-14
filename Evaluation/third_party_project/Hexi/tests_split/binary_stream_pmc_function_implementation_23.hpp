
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <string>
#include <string_view>
#include <vector>

struct StringViewAdaptorNullTerminatedResult {
	std::size_t size_after_write;
	std::string output;
	bool stream_empty;
};

/**
 * @brief Writes a std::string_view as null-terminated and reads it back.
 *
 * @param input The input string_view to write with a null terminator.
 * @return StringViewAdaptorNullTerminatedResult Stream size after write, output string, and emptiness after read.
 */
StringViewAdaptorNullTerminatedResult exercise_string_view_adaptor_null_terminated(std::string_view input) {
	std::vector<char> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	hexi::pmc::binary_stream stream(adaptor);

	stream << hexi::null_terminated(input);
	const std::size_t size_after_write = stream.size();

	std::string output;
	stream >> hexi::null_terminated(output);

	return {size_after_write, std::move(output), stream.empty()};
}
