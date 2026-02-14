
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <string>
#include <string_view>
#include <vector>

struct StringViewAdaptorDefaultResult {
	std::string output;
	bool stream_empty;
};

/**
 * @brief Round-trips a std::string_view using the default adaptor (operator<< and operator>>).
 *
 * @param input The string_view to write.
 * @return StringViewAdaptorDefaultResult The read-back string and whether the stream is empty after read.
 */
StringViewAdaptorDefaultResult exercise_string_view_adaptor_default(std::string_view input) {
	std::vector<char> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	hexi::pmc::binary_stream stream(adaptor);

	stream << input;

	std::string output;
	stream >> output;

	return {std::move(output), stream.empty()};
}
