
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <string>
#include <string_view>
#include <vector>

struct StringViewAdaptorRawResult {
	std::size_t input_size;
	std::size_t buffer_size_after_write;
	std::string output_null_terminated;
	bool stream_empty_after_read;
};

/**
 * @brief Writes a raw std::string_view containing embedded nulls, then reads back using null_terminated.
 *
 * @param input Raw bytes to write (may include '\0').
 * @return StringViewAdaptorRawResult Sizes, the truncated output read by null_terminated, and stream emptiness.
 */
StringViewAdaptorRawResult exercise_string_view_adaptor_raw(std::string_view input) {
	std::vector<char> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	hexi::pmc::binary_stream stream(adaptor);

	stream << hexi::raw(input);

	std::string output;
	stream >> hexi::null_terminated(output);

	return {
		.input_size = input.size(),
		.buffer_size_after_write = buffer.size(),
		.output_null_terminated = std::move(output),
		.stream_empty_after_read = stream.empty()
	};
}
