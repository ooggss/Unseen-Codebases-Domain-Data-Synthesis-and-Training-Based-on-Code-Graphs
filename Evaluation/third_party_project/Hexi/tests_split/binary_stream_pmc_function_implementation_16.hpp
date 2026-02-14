
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <string>
#include <vector>

struct StringAdaptorPrefixedResult {
	std::string output;
	bool stream_empty;
};

/**
 * @brief Round-trips a string using hexi::prefixed (size-prefixed) encoding.
 *
 * @param input The input string to encode and decode.
 * @return StringAdaptorPrefixedResult The decoded output and whether the stream is empty after reading.
 */
StringAdaptorPrefixedResult exercise_string_adaptor_prefixed(const std::string& input) {
	std::vector<char> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	hexi::pmc::binary_stream stream(adaptor);

	stream << hexi::prefixed(input);

	std::string output;
	stream >> hexi::prefixed(output);

	return {output, stream.empty()};
}
