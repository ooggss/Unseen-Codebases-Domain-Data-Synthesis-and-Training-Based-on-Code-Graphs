
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <cstdlib>
#include <string>
#include <vector>

struct PrefixedVarintRoundtripResult {
	std::string input;
	std::string output;
	bool stream_empty;
	bool stream_truthy;
};

/**
 * @brief Round-trips a string via hexi::prefixed_varint using a vector<char> buffer adaptor.
 *
 * Generates a random ASCII payload of @p size bytes using rand(), writes it with prefixed_varint,
 * reads it back with prefixed_varint, and returns both strings and stream status flags.
 *
 * @param size Size of the random input string to generate.
 * @return PrefixedVarintRoundtripResult Input and output strings plus whether the stream is empty and truthy.
 */
PrefixedVarintRoundtripResult exercise_prefixed_varint_string(std::size_t size) {
	std::vector<char> buffer;
	hexi::pmc::buffer_adaptor adaptor(buffer);
	hexi::pmc::binary_stream stream(adaptor);

	std::string input;
	input.resize_and_overwrite(size, [&](char* b, const std::size_t n) {
		for (std::size_t i = 0; i < n; ++i) {
			b[i] = (rand() % 127) + 32;
		}
		return n;
	});

	stream << hexi::prefixed_varint(input);

	std::string output;
	stream >> hexi::prefixed_varint(output);

	return PrefixedVarintRoundtripResult{
		.input = std::move(input),
		.output = std::move(output),
		.stream_empty = stream.empty(),
		.stream_truthy = static_cast<bool>(stream)
	};
}
