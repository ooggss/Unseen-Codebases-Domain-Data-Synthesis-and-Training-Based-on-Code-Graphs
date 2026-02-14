
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <string>
#include <string_view>
#include <vector>

struct StringViewAdaptorPrefixedResult {
	std::string output;
	bool stream_empty;
};

/**
 * @brief Round-trips a std::string_view using hexi::prefixed encoding into a std::string.
 *
 * @param input The string_view to write.
 * @return StringViewAdaptorPrefixedResult The decoded output string and whether the stream is empty.
 */
StringViewAdaptorPrefixedResult exercise_string_view_adaptor_prefixed(std::string_view input) {
	std::vector<char> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	hexi::pmc::binary_stream stream(adaptor);

	stream << hexi::prefixed(input);

	std::string output;
	stream >> hexi::prefixed(output);

	return {std::move(output), stream.empty()};
}
