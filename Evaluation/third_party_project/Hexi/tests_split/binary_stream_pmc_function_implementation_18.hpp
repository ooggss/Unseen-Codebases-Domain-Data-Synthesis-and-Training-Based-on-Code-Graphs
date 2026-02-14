
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <format>
#include <string>
#include <vector>

struct StringAdaptorRawResult {
	std::size_t input_size;
	std::size_t buffer_size_after_write;
	std::string output_null_terminated;
	bool stream_empty_after_read;
};

/**
 * @brief Writes a raw string containing embedded nulls, then reads back using null_terminated.
 *
 * The raw write preserves embedded null bytes. Reading with null_terminated stops at the first null,
 * leaving remaining bytes in the stream.
 *
 * @param embedded_null_string A string that may contain embedded '\0' bytes.
 * @return StringAdaptorRawResult Input and buffer size checks, the truncated output, and whether the stream is empty.
 */
StringAdaptorRawResult exercise_string_adaptor_raw(const std::string& embedded_null_string) {
	std::vector<char> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	hexi::pmc::binary_stream stream(adaptor);

	stream << hexi::raw(embedded_null_string);

	std::string output;
	stream >> hexi::null_terminated(output);

	return StringAdaptorRawResult{
		.input_size = embedded_null_string.size(),
		.buffer_size_after_write = buffer.size(),
		.output_null_terminated = std::move(output),
		.stream_empty_after_read = stream.empty()
	};
}
