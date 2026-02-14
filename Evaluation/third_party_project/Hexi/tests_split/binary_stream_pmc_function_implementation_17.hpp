
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <string>
#include <vector>

struct StringAdaptorDefaultResult {
	std::string output;
	bool stream_empty;
};

/**
 * @brief Round-trips a string using the default string adaptor (operator<< and operator>>).
 *
 * @param input The input string to write and then read back.
 * @return StringAdaptorDefaultResult The read-back string and whether the stream is empty afterwards.
 */
StringAdaptorDefaultResult exercise_string_adaptor_default(const std::string& input) {
	std::vector<char> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	hexi::pmc::binary_stream stream(adaptor);

	stream << input;

	std::string output;
	stream >> output;

	return {output, stream.empty()};
}
