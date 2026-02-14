
#include <hexi/pmc/binary_stream.h>
#include <hexi/pmc/buffer_adaptor.h>
#include <array>
#include <string>
#include <string_view>

struct StdArrayBehaviourResult {
	bool initial_write_threw_buffer_overflow;
	bool stream_empty_after_reset;
	bool stream_truthy_after_roundtrip;
	bool stream_empty_after_roundtrip;
	std::string output;
};

/**
 * @brief Demonstrates buffer_overflow behavior for std::array-backed adaptor and recovery after reset.
 *
 * A std::array buffer adaptor is "full" by default because size == capacity. Attempting to write
 * should throw hexi::buffer_overflow. Then adaptor.clear() and stream.clear_state() reset the state,
 * after which writing and reading a string_view succeeds.
 *
 * @param input The string_view to attempt to write before and after reset.
 * @return StdArrayBehaviourResult Whether the initial write threw, whether the stream was empty after reset,
 *         and the output/truthiness/emptiness after successful roundtrip.
 */
StdArrayBehaviourResult exercise_std_array_behaviour(std::string_view input) {
	std::array<char, 128> buffer{};
	hexi::pmc::buffer_adaptor adaptor(buffer);
	hexi::pmc::binary_stream stream(adaptor);

	StdArrayBehaviourResult res{};

	try {
		stream << input;
		res.initial_write_threw_buffer_overflow = false;
	} catch (const hexi::buffer_overflow&) {
		res.initial_write_threw_buffer_overflow = true;
	}

	adaptor.clear();
	stream.clear_state();
	res.stream_empty_after_reset = stream.empty();

	std::string output;
	stream << input;
	stream >> output;

	res.output = std::move(output);
	res.stream_empty_after_roundtrip = stream.empty();
	res.stream_truthy_after_roundtrip = static_cast<bool>(stream);
	return res;
}
